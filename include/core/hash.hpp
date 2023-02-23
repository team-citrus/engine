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
#include "core/vector.hpp"
#include "core/pair.hpp"
#include "core/mem.hpp"

namespace engine
{
    typedef size_t hash_t;

    // A SlipHash implementation, the key is based off some addresses
    // Implementation based on https://github.com/majek/csiphash/blob/master/csiphash.c
    hash_t hash(void *data, size_t bytes);

    template<class KEY, class T>
    class hashMap
    {
        size_t s;
        size_t c;
        pair<hash_t, T> *ptr;
        public:
        hashMap(pair<KEY, T> p[], size_t ss)
        {
            *this = hashMap<KEY, T>(ss);
            for(size_t i = 0; i < ss; i++)
            {
                hash_t h = hash(&p[i].a, sizeof(KEY));
                if(ptr[h % c].a == h) // Ahhhh hash collision
                {
                    // TODO: errno
                    *this = hashMap<KEY, T>(ss);
                    break;
                }
                else if(ptr[h % c].a != 0)
                {
                    size_t sc = ss;
                    
                    while(true)
                    {
                        *this = hashMap<KEY, T>((sc += 8));
                        s = ss;
                        
                        for(size_t i = 0; i < s; i++);
                        {
                            hash_t hh = hash(&p[i].a, sizeof(KEY));
                            if(ptr[hh % c].a == hh)
                            {
                                // TODO: errno
                                *this = hashMap(ss);
                                break;
                            }
                            else if(ptr[hh % c].a != 0)
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

        hashMap(Vector<pair<KEY, T>> p)
        {
            *this = hashMap<KEY, T>(p.data(), p.getCount());
        }

        hashMap(size_t cc)
        {
            s = 0;
            ptr = memalloc(sizeof(pair<hash_t,T>) * (c = cc), MEM_FLAG_UNIT_BYTE);

            memset(ptr, 0, sizeof(pair<hash_t, T>) * c);
        }

        hashMap(hashMap<KEY, T> &cc)
        {
            c = cc.c;
            s = cc.s;
            ptr = memalloc(sizeof(pair<hash_t,T>) * c, MEM_FLAG_UNIT_BYTE);
            memcpy(ptr, cc.ptr, c);
        }

        ~hashMap()
        {
            memfree(ptr);
        }

        option<T> add(KEY k, T t)
        {
            hash_t h = hash(&k, sizeof(KEY));
            if(s + 1 >= c)
            {
                iCollision:
                size_t cc = c + 8;

                while(true)
                {
                    pair<hash_t, T> *nptr = memalloc(sizeof(pair<hash_t,T>) * cc, MEM_FLAG_UNIT_BYTE);
                    memset(nptr, 0, sizeof(pair<hash_t,T>) * cc);

                    for(size_t i = 0; i < c; i++)
                    {
                        hash_t in = ptr[i].a;
                        if(nptr[in % cc].a != 0)
                        {
                            memfree(nptr);
                            cc += 8;
                            continue;
                        }
                        else
                            nptr[in % cc] = ptr[i];
                    }

                    if(nptr[h % cc].a != 0)
                    {
                        memfree(nptr);
                        cc += 8;
                        continue;
                    }
                    else
                        nptr[h % cc] = pair<hash_t,T>(h, t);

                    memfree(ptr);
                    ptr = nptr;
                    c = cc;
                    s++;
                }
            }
            else
            {
                if(ptr[h % c].a == h) // Ahhhhh hash collision
                    return none<T>();
                else if(ptr[h % c].a != 0)
                    goto iCollision;
                else
                {
                    ptr[h % c].a = h;
                    ptr[h % c].b = t;
                    s++;
                    return ptr[h % c].b;
                }
            }
        }

        OPERATOR size_t getCount()
        {
            return s;
        }

        void rm(KEY k)
        {
            memset(&this[k], 0, sizeof(pair<hash_t, T>));
            s--;

            if(s <= c - 8)
            {
                Vector<pair<KEY, T>> v;
                for(size_t i = 0; i < c; i++)
                {
                    if(ptr[i].a != 0)
                        v.push(ptr[i]);
                }
                
                hashMap<KEY, T> tmp(v);
                
                // TODO: errno checks
                
                *this = tmp;
            }
        }

        OPERATOR T &operator[](KEY k)
        {
            return ptr[hash(&k, sizeof(KEY)) % c];
        }
    };
    
    uint32_t crc32(void *data, size_t s);
}

#endif
