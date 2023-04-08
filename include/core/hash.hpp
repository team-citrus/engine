/*
*   name: include/core/hash.hpp
*   origin: Citrus Engine
*   purpose: Provide the main hash function, and hashMap<K, T>
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
	typedef size_t hash_t;

	// TODO: std::hash style struct

	// A SlipHash implementation, the key is based off some addresses
	// Implementation based on https://github.com/majek/csiphash/blob/master/csiphash.c
	hash_t hash(void *data, size_t bytes);

	template<class KEY, class T>
	class hashMap
	{
		size_t s;
		size_t c;
		Pair<hash_t, T> *ptr;
		public:
		OPTIMIZE(3) hashMap(Pair<KEY, T> p[], size_t ss)
		{
			*this = hashMap<KEY, T>(ss);
			for(size_t i = 0; i < ss; i++)
			{
				hash_t h = hash(&p[i].first, sizeof(KEY));
				if(ptr[h % c].first == h) // Ahhhh hash collision
				{
					engine::errorcode() = ENGINE_HASH_COLLISION;
					*this = hashMap<KEY, T>(ss);
					break;
				}
				else if(ptr[h % c].first != 0)
				{
					size_t sc = ss;
					
					while(true)
					{
						*this = hashMap<KEY, T>((sc += 8));
						s = ss;
						
						for(size_t i = 0; i < s; i++);
						{
							hash_t hh = hash(&p[i].first, sizeof(KEY));
							if(ptr[hh % c].first == hh)
							{
								engine::errorcode() = ENGINE_HASH_COLLISION;
								*this = hashMap(ss);
								break;
							}
							else if(ptr[hh % c].first != 0)
							{
								memfree(ptr);
								break;
							}
							else
								ptr[hh % c] = p [i];
						}
					}
				}
				else
				{
					ptr[h % c] = p[i]
				}
			}
		}

		OPTIMIZE(3) hashMap(Vector<Pair<KEY, T>> p)
		{
			*this = hashMap<KEY, T>(p.data(), p.getCount());
		}

		OPTIMIZE(3) hashMap(size_t cc)
		{
			s = 0;
			ptr = zmalloc(sizeof(Pair<hash_t,T>) * (c = cc));
		}

		OPTIMIZE(3) hashMap(hashMap<KEY, T> &cc)
		{
			c = cc.c;
			s = cc.s;
			ptr = memcalloc(sizeof(Pair<hash_t,T>) * c);
			memcpy(ptr, cc.ptr, c); // TODO: Do some speed comparison against ymm_memcpy(ptr, cc.ptr, (size & 0x1F) ? (size >> 5) + 1 : size >> 5);
		}

		~hashMap()
		{
			memfree(ptr);
		}

		OPTIMIZE(3) 

		#ifdef _FILE_IS_ERRNO_DOT_CPP_
		OPERATOR
		#endif

		Option<T> add(KEY k, T t)
		{
			hash_t h = hash(&k, sizeof(KEY));
			if(s + 1 >= c)
			{
				iCollision:
				size_t cc = c + 8;

				while(true)
				{
					Pair<hash_t, T> *nptr = memcalloc(sizeof(Pair<hash_t,T>) * cc);

					for(size_t i = 0; i < c; i++)
					{
						hash_t in = ptr[i].first;
						if(nptr[in % cc].first != 0)
						{
							memfree(nptr);
							cc += 8;
							continue;
						}
						else
							nptr[in % cc] = ptr[i];
					}

					if(nptr[h % cc].first == h)
					{
						memfree(nptr);

						#ifndef _FILE_IS_ERRNO_DOT_CPP_
						engine::errorcode() = ENGINE_HASH_COLLISION;
						#endif

						return none<T>(); 
					}
					else if(nptr[h % cc].first != 0)
					{
						memfree(nptr);
						cc += 8;
						continue;
					}
					else
						nptr[h % cc] = Pair<hash_t,T>(h, t);

					memfree(ptr);
					ptr = nptr;
					c = cc;
					s++;
				}
			}
			else
			{
				if(ptr[h % c].first == h) // Ahhhhh hash collision
				{
					#ifndef _FILE_IS_ERRNO_DOT_CPP_
					engine::errorcode() = ENGINE_HASH_COLLISION;
					#endif

					return none<T>();
				}
				else if(ptr[h % c].first != 0)
					goto iCollision;
				else
				{
					ptr[h % c].first = h;
					ptr[h % c].second = t;
					s++;
					return ptr[h % c].second;
				}
			}
		}

		OPERATOR size_t getCount()
		{
			return s;
		}

		OPTIMIZE(3) void rm(KEY k)
		{
			memset(this + k, 0, sizeof(Pair<hash_t, T>));
			s--;

			if(s <= c - 8)
			{
				Vector<Pair<KEY, T>> v;
				for(size_t i = 0; i < c; i++)
				{
					if(ptr[i].first != 0)
						v.push(ptr[i]);
				}
				
				hashMap<KEY, T> tmp(v);
				
				*this = tmp;
			}
		}

		OPERATOR T &operator[](KEY k)
		{
			return ptr[hash(&k, sizeof(KEY)) % c].second;
		}

		OPERATOR bool hasItem(KEY k)
		{
			return (ptr[hash(&k, sizeof(KEY)) % c].first != 0);
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
