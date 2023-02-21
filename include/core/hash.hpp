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
        pair<hash_t, T> *ptr;
        public:
        hashMap(pair<KEY, T> p[], size_t ss)
        {
            ptr = memalloc(sizeof(pair<hash_t, T>) * ss, 0);
            s = ss;
            for(size_t i = 0; i < s; i++)
                ptr[hash(&p[i].a, sizeof(KEY)) % s] = pair(hash(&p[i].a, sizeof(KEY)), p[i].b);
        }

        hashMap(Vector<pair<KEY, T>> p)
        {
            ptr = memalloc(sizeof(pair<hash_t, T>) * p.count(), 0);
            s = p.count();
            for(size_t i = 0; i < s; i++)
                ptr[hash(&p[i].a, sizeof(KEY)) % s] = pair(hash(&p[i].a, sizeof(KEY)), p[i].b);
        }

        OPERATOR void add(KEY k, T t) // Probably won't work with maps with few members
        {
            pair<hash_t, T> *nptr = memalloc(sizeof(pair<hash_t, T>) * (s + 1), 0);
            for(size_t i = 0; i < s; i++)
                nptr[ptr[i].a % (s + 1)] = ptr[i];

            memfree(ptr);
            nptr[hash(&k, sizeof(KEY)) % (s + 1)] = pair(hash(&k, sizeof(KEY)), t);
            ptr = nptr;
        }

        OPERATOR size_t getCount()
        {
            return s;
        }

        OPERATOR void rm(KEY k)
        {
            pair<hash_t, T> *nptr = memalloc(sizeof(pair<hash_t, T>) * (s - 1), 0);
            hash_t h = hash(&k, sizeof(KEY));
            for(size_t i = 0; i < s; i++)
                if(ptr[i].a != h)
                    nptr[ptr[i].a % (s - 1)] = ptr[i];

            memfree(ptr);
            ptr = nptr;
        }

        OPERATOR T operator[](KEY k)
        {
            return ptr[hash(&k, sizeof(KEY)) % s];
        }
    };
    
    uint32_t crc32(void *data, size_t s);
}

#endif
