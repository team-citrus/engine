/*
*   name: core/pair.hpp
*   origin: Citrus Engine
*   purpose: Provide pairs and maps
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PAIRS_HPP___
#define CITRUS_ENGINE_PAIRS_HPP___

#include "core/vector.hpp"

namespace engine
{
    template <typename A, typename B>
    class pair
    {
        public:
        pair(A aa, B bb)
        {
            a = aa;
            b = bb;
        }
        A a;
        B b;
    };

    template <typename A, typename B>
    class map
    {
        public:
        OPERATOR void addPair(A a, B b)
        {
            vec.push(pair<A, B>(a, b));
        }

        OPERATOR void addPair(pair<A, B> p)
        {
            vec.push(p);
        }

        OPERATOR pair<A, B> &getPair(A a)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].a == a)
                    return vec[i];
            }
        }

        OPERATOR pair<A, B> &getPair(B b)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].b == b)
                    return vec[i];
            }
        }

        OPERATOR B &getB(A a)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].a == a)
                    return vec[i].b;
            }
        }

        OPERATOR A &getA(B b)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].b == b)
                    return vec[i].a;
            }
        }

        private:
        Vector<pair<A, B>> vec;
    };
};

#endif