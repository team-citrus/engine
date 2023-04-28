/*
*   name: include/core/string.hpp
*   origin: Citrus Engine
*   purpose: Provide better more unicode friendly strings.
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#ifndef CITRUS_ENGINE_STRING_HPP__
#define CITRUS_ENGINE_STRING_HPP__

#include <cstring>
#include <string>
#include "core/mem.hpp"
#include "core/vector.hpp"
#include "core/errno.hpp"

namespace engine
{
	// A better, unicode compatible string class
	class String
	{
		uint8_t *ptr;
		size_t length;
		size_t capacity;
		size_t charCount;
		uint32_t ich;
		size_t pos; // Necessary evil
		public:
		String()
		{
			ptr = (uint8_t*)memalloc((capacity = 32));
			length = 0;
		}
		String(const char *str) // TODO: errorcheck
		{
			ptr = (uint8_t*)memalloc((capacity = (length = strlen(str)) + 32));
			strcpy((char*)ptr, str);
		}
		OPERATOR String &operator<<(uint32_t uchar)
		{
			uint8_t encode[4];
			int encoded = 0;
			if(uchar < 0x10FFFF) // Invalid codepoints
			{
				errorcode() = ENGINE_INVALID_ARG;
				return *this << 0xFFFD;
			}`

			if(uchar <= 0x10000)
			{
				encoded = 4;
				encode[0] = 0xF8 | ((uchar >> 18) & 0x7);
				encode[1] = 0x80 | ((uchar >> 12) & 0x3F);
				encode[2] = 0x80 | ((uchar >> 6) & 0x3F);
				encode[3] = 0x80 | (uchar & 0x3F);
			}
			else if(uchar <= 0x800)
			{
				encoded = 3;
				encode[0] = 0xE0 | ((uchar >> 12) & 0xF);
				encode[1] = 0x80 | ((uchar >> 6) & 0x3F);
				encode[2] = 0x80 | (uchar & 0x3F);
			}
			else if(uchar <= 0x80)
			{
				encoded = 2;
				encode[0] = 0xC0 | ((uchar >> 6) & 0x1F);
				encode[1] = 0x80 | (uchar & 0x3F);
			}
			else
			{
				encoded = 1;
				encode[0] = uchar;
			}

			if((length += encoded) > capacity)
			{
				capacity = length + 32;
				ptr = (uint8_t*)memrealloc(ptr, capacity);
			}

			for(int i = 0; i < encoded; i++)
				ptr[(length - encoded - 1) + i] = encode[i];

			charCount++;
		}
		OPERATOR String &operator<<(const char *str) // this won't work with any encoding but ASCII/UTF-8
		{	// TODO: Error check the resulting string
			size_t oldLen = length;
			if((length += strlen(str)) > capacity)
			{
				capacity = length + 32;
				ptr = (uint8_t*)memrealloc(ptr, capacity);
			}

			memcpy(ptr + oldLen, str, strlen(str));
			return *this;
		}

		#ifdef _WIN32
		#define CHAR16 wchar_t
		#define CHAR32 char32_t
		#else
		#define CHAR16 char16_t
		#define CHAR32 wchar_t
		#endif

		OPERATOR String &operator<<(const CHAR16 *str)
		{
			// TODO: Optimize this
			if(str[0] == 0xFFFE)
			{
				for(size_t i = 1; i < std::char_traits<CHAR16>::length(str); i++)
				{
					CHAR16 ch = (str[i] >> 8) | (str[i] << 8);
					if(ch >= 0xD800 && 0xDFFF >= ch)
					{
						CHAR16 ch2;
						if(i + 1 < std::char_traits<char16_t>::length(str) && ((ch2 = (str[i + 1] >> 8) | (str[i + 1] << 8)) >= 0xD800 && 0xDFFF >= ch2))
						{
							uint32_t codepoint = ((ch - 0xD800) << 10) + ((ch2 - 0xDC00));
							codepoint += 0x10000;
							*this << codepoint;
							i += 2;
							continue;
						}
						else
							*this << ch;
					}
				}
			}
			else
			{
				for(size_t i = 1; i < std::char_traits<char16_t>::length(str); i++)
				{
					CHAR16 ch = str[i];
					if(ch >= 0xD800 && 0xDFFF >= ch)
					{
						CHAR16 ch2;
						if(i + 1 < std::char_traits<char16_t>::length(str) && (ch2 = str[i + 1]) >= 0xD800 && 0xDFFF >= ch2)
						{
							uint32_t codepoint = ((ch - 0xD800) << 10) + ((ch2 - 0xDC00));
							codepoint += 0x10000;
							*this << codepoint;
							i += 2;
							continue;
						}
						else
							*this << ch;
					}
				}
			}

			return *this;
		}

		OPERATOR String &operator<<(const CHAR32 *str) // UTF-32/raw codepoints
		{
			size_t strSize;
			uint8_t *nstr;
			for(size_t i = 0; i < std::char_traits<CHAR32>::length(str); i++)
			{
				if(str[i] <= 0x7F)
					strSize++;
				else if(str[i] <= 0x7FF)
					strSize += 2;
				else if(str[i] <= 0xFFFF)
					strSize += 3;
				else if(str[i] <= 0x10FFFF)
					strSize += 4;
			}

			nstr = (uint8_t*)memalloc(strSize);
			size_t cur = 0;
			for(size_t i = 0; i < std::char_traits<CHAR32>::length(str); i++)
			{
				if(str[i] & (~0x7F) == 0)
					nstr[cur++] = (uint8_t)(str[i] & 0x7F);
				else if(str[i] & (~0x7FF) == 0)
				{
					nstr[cur++] = (uint8_t)((str[i] >> 6) & 0x1F) | 0xC0;
					nstr[cur++] = (uint8_t)(str[i] & 0x3F) | 0x80;
				}
				else if(str[i] & (~0xFFFF) == 0)
				{
					nstr[cur++] = (uint8_t)((str[i] >> 12) & 0xF) | 0xE0;
					nstr[cur++] = (uint8_t)((str[i] >> 6) & 0x3F) | 0x80;
					nstr[cur++] = (uint8_t)(str[i] & 0x3F) | 0x80;
				}
				else
				{
					nstr[cur++] = (uint8_t)((str[i] >> 18) & 0x7) | 0xF0;
					nstr[cur++] = (uint8_t)((str[i] >> 12) & 0x3F) | 0x80;
					nstr[cur++] = (uint8_t)((str[i] >> 6) & 0x3F) | 0x80;
					nstr[cur++] = (uint8_t)(str[i] & 0x3F) | 0x80;
				}
			}

			if(length + strSize > capacity)
			{
				capacity = length + strSize + 32;
				ptr = (uint8_t*)memrealloc(ptr, capacity);
				memcpy(ptr + length, nstr, strSize);
				length += strSize;
				charCount += std::char_traits<CHAR32>::length(str);
			}

			return *this;
		}

		OPERATOR String &operator<<(const String &str)
		{
			*this << str.data();
		}

		OPERATOR String &operator+=(const char *str)
		{
			return *this << str;
		}

		OPERATOR String &operator+=(const CHAR16 *str)
		{
			return *this << str;
		}

		OPERATOR String &operator+=(const CHAR32 *str)
		{
			return *this << str;
		}

		OPERATOR String &operator+=(const String &str)
		{
			return *this << str;
		}

		OPERATOR void append(const char *str)
		{
			*this << str;
		}

		OPERATOR void append(const CHAR16 *str)
		{
			*this << str;
		}

		OPERATOR void append(const CHAR32 *str)
		{
			*this << str;
		}

		OPERATOR void append(const String &str)
		{
			*this << str;
		}

		OPERATOR void append(const uint32_t c)
		{
			*this << c;
		}

		OPERATOR size_t length() const
		{
			return charCount;
		}

		OPERATOR uint32_t operator[](size_t index) const
		{
			size_t offset = 0;
			for(size_t i = 0; i < index; i++)
			{
				if(ptr[offset] & 0x80 == 0)
				{
					offset++;
				}
				else
				{
					offset++;
					while(ptr[offset] & 0x80 != 0 && ptr[offset] & 0x40 == 0) offset++;
				}
			}

			if(ptr[offset] & 0x80 != 0x80)
			{
				uint32_t code;
				uint8_t encoded[4] = { 0, 0, 0, 0 };
				encoded[0] = ptr[offset];
				size_t i = 1;
				while(ptr[offset] & 0x80 != 0 && ptr[offset] & 0x40 == 0)
				{
					encoded[i++] = ptr[offset++];
				}
				for(i = 0; i < 4; i++)
				{
					if(encoded[i]==0) break;
				}
				
				switch(i)
				{
					case 2:
					code = ((encoded[0] & 0x1F) << 6) | (encoded[1] & 0x3F);
					break;
					case 3:
					code = ((encoded[0] & 0xF) << 12) | ((encoded[1] & 0x3F) << 6) | (encoded[2] & 0x3F); 
					break;
					case 4:
					code = ((encoded[0] & 0x7) << 18) | ((encoded[1] & 0x3F) << 12) | ((encoded[2] & 0x3F) << 6) | (encoded[3] & 0x3F);
					break;
					default:
					code = 0xFFFD; // Used as a replacement character thing;
				}
				return code;
			}
			else
			{
				return ptr[offset];
			}
		}

		OPERATOR uint32_t at(size_t index) const
		{
			return (*this)[index];
		}


		// Hacky solutions but whatever
		OPERATOR void writeAt(size_t index, uint32_t ch)
		{
			String tmp;
			tmp << (data() + index);
			length -= tmp.length;
			charCount -= tmp.charCount;
			*this << ch << tmp;
		}
		OPERATOR void writeAt(size_t index, const String &str)
		{
			String tmp;
			tmp << (data() + index);
			length -= tmp.length;
			charCount -= tmp.charCount;
			*this << str << tmp;
		}
		OPERATOR void writeAt(size_t index, const char *str)
		{
			String tmp;
			tmp << (data() + index);
			length -= tmp.length;
			charCount -= tmp.charCount;
			*this << str << tmp;
		}
		OPERATOR void writeAt(size_t index, const CHAR16 *str)
		{
			String tmp;
			tmp << (data() + index);
			length -= tmp.length;
			charCount -= tmp.charCount;
			*this << str << tmp;
		}
		OPERATOR void writeAt(size_t index, const CHAR32 *str)
		{
			String tmp;
			tmp << (data() + index);
			length -= tmp.length;
			charCount -= tmp.charCount;
			*this << str << tmp;
		}
	
		// TODO: More member functions

		OPERATOR char *data()
		{
			return (char*)ptr;
		}

		OPERATOR const char *data() const
		{
			return (char*)ptr;
		}

		OPERATOR size_t byteCount() const
		{
			return length;
		}

		OPERATOR void asUTF16LE(CHAR16 *str, size_t maxLen, bool BOM) const
		{
			if(BOM)
			{
				maxLen--;
				*str++ = 0xFEFF;
			}

			size_t i = 0;
			while (maxLen)
			{
				if(ptr[i] & 0x80 == 0)
				{
					maxLen--;
					*str++ = (uint16_t)ptr[i++];
				}
				else if(ptr[i] & 0xE0 == 0xC0)
				{
					maxLen--;
					*str++ = ((ptr[i] & 0x1F) << 6) | (ptr[i + 1] & 0x3F);
				}
				else if(ptr[i] & 0xF0 == 0xE0)
				{
					maxLen--;
					*str++ = ((ptr[i] & 0xF) << 12) | ((ptr[i + 1] & 0x3F) << 6) | (ptr[i + 2] & 0x3F);
				}
				else if(ptr[i] & 0xF8 == 0xF0)
				{
					if(maxLen < 2)
						return;

					uint32_t codepoint = 
					((ptr[i] & 0x7) << 18) |
					((ptr[i + 1] & 0x3F) << 12) |
					((ptr[i + 2] & 0x3F) << 6) |
					(ptr[i + 3] & 0x3F);

					uint16_t surrogateA = (uint16_t)((codepoint -= 0x10000) >> 10) | 0xD800;
					uint16_t surrogateB = (uint16_t)(codepoint & 0x3FF) | 0xDC00;
					maxLen -= 2;
					*str++ = surrogateA;
					*str++ = surrogateB;
				}
			}
		}
	};
}

#undef CHAR32
#undef CHAR16

#endif 