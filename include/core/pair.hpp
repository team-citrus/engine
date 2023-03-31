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
	class Pair
	{
		public:
		Pair(A aa, B bb)
		{
			a = aa;
			b = bb;
		}
		A a;
		B b;
	};

	template <typename K, typename B>
	class Map
	{
		public:
		OPERATOR void addPair(A a, B b)
		{
			vec.push(Pair<A, B>(a, b));
		}

		OPERATOR void addPair(Pair<A, B> p)
		{
			vec.push(p);
		}

		OPERATOR Option<Pair<A, B>> &lookupPair(A a)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].a == a)
					return Option::Option::some(vec[i]);
			}
		}

		OPERATOR Option<Pair<A, B>> &lookupPair(B b)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].b == b)
					return Option::some(vec[i]);
			}
			return none<Pair<A, B>>();
		}

		OPERATOR Option<B&> getB(A a)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].a == a)
					return Option::some<B&>(vec[i].b);
			}
			return none<B&>();
		}

		OPERATOR Option<A&> getA(B b)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].b == b)
					return Option::some<A&>(vec[i].a);
			}
			return none<A&>();
		}

		OPERATOR Option<A&> lookup(B b)
		{
			return this->getA(b);
		}

		OPERATOR Option<B&> &lookup(A a)
		{
			return this->getB(a);
		}

		OPERATOR Option<A&> operator[](A a)
		{
			return lookup(a);
		}

		OPERATOR Option<B&> operator[](B b)
		{
			return lookup(b);
		}

		private:
		Vector<Pair<A, B>> vec;
	};

	// TODO: iterators
};

#endif