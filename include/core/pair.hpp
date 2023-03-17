/*
*   name: include/core/pair.hpp
*   origin: Citrus Engine
*   purpose: Provide pairs and maps
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PAIRS_HPP___
#define CITRUS_ENGINE_PAIRS_HPP___

#include "core/option.hpp"
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

    template <typename K, typename B>
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

        OPERATOR option<pair<A, B>> &lookupPair(A a)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].a == a)
                    return option::option::some(vec[i]);
            }
        }

        OPERATOR option<pair<A, B>> &lookupPair(B b)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].b == b)
                    return option::some(vec[i]);
            }
            return none<pair<A, B>>();
        }

        OPERATOR option<B&> getB(A a)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].a == a)
                    return option::some<B&>(vec[i].b);
            }
            return none<B&>();
        }

        OPERATOR option<A&> getA(B b)
        {
            for(int i = 0; i < vec.getCount(); i++)
            {
                if(vec[i].b == b)
                    return option::some<A&>(vec[i].a);
            }
            return none<A&>();
        }

        OPERATOR option<A&> lookup(B b)
        {
            return this->getA(b);
        }

        OPERATOR option<B&> &lookup(A a)
        {
            return this->getB(a);
        }

        OPERATOR option<A&> operator[](A a)
        {
            return lookup(a);
        }

        OPERATOR option<B&> operator[](B b)
        {
            return lookup(b);
        }

        private:
        Vector<pair<A, B>> vec;
    };
};

#endif