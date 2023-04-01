/*
*   name: include/core/pair.hpp
*   origin: Citrus Engine
*   purpose: Provide pairs and maps
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PAIRS_HPP___
#define CITRUS_ENGINE_PAIRS_HPP___

#include <utility>
#include "core/option.hpp"
#include "core/vector.hpp"

namespace engine
{
	template <typename A, typename B>
	using Pair = std::pair<A, B>

	template <typename K, typename T>
	class Map
	{
		public:
		using key_type = K;
		using mapped_type = T;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		// TODO: Other std::map compat stuff.
		
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
				if(vec[i].first == a)
					return Option::Option::some(vec[i]);
			}
		}

		OPERATOR Option<Pair<A, B>> &lookupPair(B b)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].second == b)
					return Option::some(vec[i]);
			}
			return none<Pair<A, B>>();
		}

		OPERATOR Option<B&> getB(A a)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].first == a)
					return Option::some<B&>(vec[i].second);
			}
			return none<B&>();
		}

		OPERATOR Option<A&> getA(B b)
		{
			for(int i = 0; i < vec.getCount(); i++)
			{
				if(vec[i].first == b)
					return Option::some<A&>(vec[i].first);
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