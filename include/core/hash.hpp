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
#include "core/extensions.h"
#include "core/vector.hpp"
#include "core/pair.hpp"
#include "core/mem.hpp"
#include "core/simd.h"
#include "core/errno.hpp"

namespace engine
{
	namespace internals { int siphash(const void *in, const size_t inlen, const void *k, uint8_t *out,
            const size_t outlen); }
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
		public:
		HashMap(Vector<Pair<KEY, T>> v)
		{
			vec = Vector((empty = v.getCount() * 2));
			for(size_t i = 0; i < v.getCount(); i++)
			{
				hash_t h = hash(&v[i].first, 1);
				size_t index = h % vec.getCount();
				size_t tries;
				while(vec[index].first != 0)
				{
					if(vec[index].first == h)
					{
						vec.~Vector();
						#ifndef _FILE_IS_ERRNO_DOT_CPP_
						errorcode() = ENGINE_INVALID_ARG;
						#endif

						return;
					}
					tries++;
					if(tries > vec.getCount())
					{
						vec.resize(vec.getCount() + 10);
						tries = 0;
						continue;
					}

					index = (h + ((tries + (tries * tries))/2)) % vec.getCount();
				}

				vec[index].first = h;
				vec[index].second = v[i].second;
			}
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