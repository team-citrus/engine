/*
*   name: include/core/hash.hpp
*   origin: Citrus Engine
*   purpose: Provide the main hash function, and HashMap<K, T>
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_HASH_HPP___
#define CITRUS_ENGINE_HASH_HPP___

#include <cstddef>
#include <cstdint>
#include <cstring>
#include "../core/extensions.h"
#include "../core/vector.hpp"
#include "../core/pair.hpp"
#include "../core/mem.hpp"
#include "../core/simd.h"
#include "../core/errno.hpp"

#define CALCULATE_POLYNOMIAL(h, tries, vec) = ((h + ((tries + (tries * tries))/2)) % vec.getCount())

namespace engine
{
	namespace internals { int siphash(const void *in, const size_t inlen, const void *k, uint8_t *out, const size_t outlen); }
	typedef size_t hash_t;

	template <class T>
	hash_t hash(T *ptr, size_t len)
	{
		return hash(ptr, len, { 'a', 'd', 'd', ' ', 'k', 'e', 'y', '\0'} );
	}

	template <class T>
	hash_t hash(T *ptr, size_t len, uint8_t *key)
	{
		return hash<uint8_t>((uint8_t*)ptr, len * sizeof(T), key);
	}

	template <>
	hash_t hash<uint8_t>(uint8_t *ptr, size_t len, uint8_t *key)
	{
		hash_t h;
		internals::siphash(ptr, len, key, (uint8_t*)&h, 8);
		return h;
	}

	template<class KEY, class T>
	class HashMap
	{
		size_t empty;
		Vector<Pair<hash_t, T>> vec;

		bool has(hash_t h)
		{
			for(size_t i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].first == h)
					return true;
			}

			return false;
		}

		void recalculate(size_t newSize) // TODO: optimize this
		{
			Vector<Pair<hash_t, T>> newVec;
			size_t newEmpty = newSize;
			
		Calculate:
			for(size_t i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].first == 0)
					continue;

				while(v[index].first != 0)
				{
					if(v[index].first == h)
					{
						#ifndef _FILE_IS_ERRNO_DOT_CPP_
						errorcode() = ENGINE_INVALID_ARG;
						#endif

						return -1;
					}
					tries++; // TODO: Load factor
					if(tries > vec.getCount())
					{
						v.resize(vec.getCount() + 10);
						e += 10;
						tries = 0;
						goto Calculate;
					}

					index = CALCULATE_POLYNOMIAL(h, tries, vec);
				}
			}

			vec.~Vector();
			vec = newVec;
			empty = newEmpty;
		}

		size_t append(hash_t h, T t)
		{
			size_t index = h % vec.getCount();
			size_t tries = 0;

			while(vec[index].first != 0)
			{
				if(vec[index].first == h)
				{
					#ifndef _FILE_IS_ERRNO_DOT_CPP_
					errorcode() = ENGINE_INVALID_ARG;
					#endif

					return -1;
				}

				tries++;
				if(tries > vec.getCount())
				{
					recalculate(vec.getCount() + 10);
				}

				index = CALCULATE_POLYNOMIAL(h, tries, vec);
			}

			vec[index].first = h;
			vec[index].second = t;
			empty--;
			
			while(((vec.getCount() - empty) * 100)/(vec.getCount() * 100) >= 75)
			{
				recalculate(vec.getCount() * 2);
			}

			return index;
		}

		size_t remove(hash_t h)
		{
			size_t index = h % vec.getCount();
			size_t tries = 0;

			while(vec[index].first != h)
			{
				if(tries == vec.getCount())
				{
					if(!has(h))
					{
						errorcode() = ENGINE_INVALID_ARG;
						return -1
					}
				}

				tries++;
				index = CALCULATE_POLYNOMIAL(h, tries, vec);
			}

			vec[index].first = 0;
			empty++;

			while(((vec.getCount() - empty) * 100)/(vec.getCount() * 100) < 25)
			{
				recalculate(vec.getCount()/2);
			}

			return index;
		}

		public:
		HashMap(Vector<Pair<KEY, T>> v)
		{
			vec = Vector((empty = v.getCount() * 2));
			for(size_t i = 0; i < v.getCount(); i++)
			{
				hash_t h = hash(&v[i].first, 1);
				if(append(h, v[i].second) == -1)
				{
					vec.~Vector();
					errorcode() = ENGINE_INVALID_ARG;
					return;
				}
			}
		}

		// TODO: Other constructors
		
		Option<T&> add(KEY &k, T t)
		{
			size_t index = append(hash(&k, sizeof(KEY)), t);

			if(index == -1)
				return Option<T&>::none();
			else
				return Option<T&>::some(vec[index].second);
		}

		void rm(KEY &k)
		{
			size_t index = remove(hash(&k, 1));
			vec[index].second.~T();
		}

		bool has(KEY &k)
		{
			return has(hash(&k, 1));
		}

		Option<T&> operator[](KEY &k)
		{
			size_t tries = 0;
			hash_t h = hash(&k, 1);
			size_t index = h % vec.getCount();

			while(vec[index].first != h)
			{
				if(tries == vec.getCount())
				{
					if(!has(k))
						return Option<T&>::none();
				}

				index = CALCULATE_POLYNOMIAL(h, tries, vec);
			}

			return vec[index].second;
		}
	};
	
	OPERATOR uint32_t crc32(void *data, size_t s)
	{
		uint32_t ret = 0xFFFFFFFF;
		uint8_t *ddata = (uint8_t*)data;
	
		for(size_t i = 0; i < s; i++)
			ret = crc32_u32(ret, *(uint32_t*)&(ddata[i])); // I love amd64 assembly instructions and intrinsics
	
		return ret;
	}
}

#endif