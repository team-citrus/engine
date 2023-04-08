/*
*   name: include/core/pair.hpp
*   origin: Citrus Engine
*   purpose: Provide pairs and maps
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PAIRS_HPP___
#define CITRUS_ENGINE_PAIRS_HPP___

#include <type_traits>
#include <utility>
#include <cstring>
#include "core/option.hpp"
#include "core/vector.hpp"

namespace engine
{
	template <typename A, typename B>
	using Pair = std::pair<A, B>;

	template <typename K, typename T>
	class Map
	{
		struct No {}; 
		template<typename T, typename Arg> No operator== (const T&, const Arg&);
		template<typename T, typename Arg> No operator< (const T&, const Arg&);
		template<typename T, typename Arg> No operator> (const T&, const Arg&);

		template<typename T, typename Arg = T>
  		struct ExistingOperators
  		{
    		enum
			{ 
				equal = !std::is_same<decltype(std::declval<T>() == std::declval<Arg>()), ::No>::value,
				lesser = !std::is_same<decltype(std::declval<T>() < std::declval<Arg>()), ::No>::value,
				greater = !std::is_same<decltype(std::declval<T>() > std::declval<Arg>()), ::No>::value,
			};
  		};

		class Node
		{
			public:
			Node()
			{
				memset(this, 0, sizeof(Node));
			}
			Node(bool clr)
			{
				*this = Node();
				this->color = clr;
			}
			Node(bool clr, Pair<K, T> p)
			{
				*this = Node(clr);
				this->pair = p;
			}
			~Node()
			{
				if(leafA != NULL) delete leafA;
				if(leafB != NULL) delete leafB;
			}
			bool color;
			Node *leafA;
			Node *leafB;
			Pair<K, T> pair;
		}

		Node *tree;
		public:
		using key_type = K;
		using mapped_type = T;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		// TODO: More std::map compatablity stuff

		Map()
		{
			tree = new Node();
		}
		~Map()
		{
			delete tree;
		}

		// TODO: Stuff.
	};

	// TODO: iterators
};

#endif