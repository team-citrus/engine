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
#include "core/extensions.h"
#include "core/errno.hpp"

namespace engine
{
	template <typename A, typename B>
	using Pair = std::pair<A, B>;

	template <typename K, typename T, typename Compare = std::less<K>>
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
			Node(const &Node cc)
			{
				color = cc.color;
				pair = cc.pair;
				parent = NULL;

				if(cc.leafA != NULL)
				{
					leafA = new Node(cc.leafA);
					leafA->parent = this;
				}
				if(cc.leafB != NULL)
				{
					leafB = new Node(cc.leafB);
					leafB->parent = this;
				}
			}
			~Node()
			{
				if(leafA != NULL) delete leafA;
				if(leafB != NULL) delete leafB;
			}

			Node &traverse(size_t &depth)
			{
				Node &val;

				if(leafB != NULL) val = leafB->traverse(depth);
				if(depth == 0) return val;

				val = *this;
				depth--;
				if(depth == 0) return val;

				if(leafA != NULL) val = leafA->traverse(depth);
				return val;
			}

			T &search(K key)
			{
				getNode(key).pair.second;
			}

			Node &getNode(K key)
			{
				if(this == NULL) // Let's prey that it will call even if NULL
				{
					engine::errorcode = ENGINE_INVALID_ARG; // Remember kids, always check for error
					return tree;
				}

				if(eqKey(pair.first, key))
					return this;

				if(Compare(pair.first, key))
					return leafA->getNode(key);
				else
					return leafB->getNode(key);
			}

			T *insert(K key, T obj)
			{
				if(Compare(pair.first, key))
				{
					if(leafA == NULL)
					{
						leafA = new Node(true, Pair<K, T>(key, obj));
						leafB->parent = this;
						if(parent != NULL) leafA->fix(); // No need to fix if we are root.
						return &leafA->pair.second;
					}
					else
						return leafA->insert(key, obj);
				}
				else
				{
					if(leafB == NULL)
					{
						leafB = new Node(true, Pair<K, T>(key, obj)); // TODO: errors.
						leafB->parent = this;
						if(parent != NULL) leafB->fix(); // No need to fix if we are root.
						return &leafB->pair.second;
					}
					else
						return leafB->insert(key, obj);
				}
			}

			void deleteNode()
			{
				if(leafA == NULL && leafB == NULL)
				{
					if(this == parent->leafA)
						parent->leafA = NULL;
					else
						parent->leafB = NULL;

					Node esto = *this; // this in spanish, node is masculine in spanish hence esto not este
					leafA->deleteFix(esto);
					delete this;
					return;
				}

				if(leafA != NULL && leafB == NULL)
				{
					if(this == parent->leafA)
						parent->leafA = leafA;
					else
						parent->leafB = leafA;

					leafA = NULL;
					Node esto = *this; // this in spanish, node is masculine in spanish hence esto not este
					leafA->deleteFix(esto);
					delete this;
					return;
				}

				if(leafA == NULL && leafB != NULL)
				{
					if(this == parent->leafA)
						parent->leafA = leafB;
					else
						parent->leafB = leafB;

					leafB = NULL;
					Node esto = *this; // this in spanish, node is masculine in spanish hence esto not este
					leafB->deleteFix(esto);
					delete this;
					return;
				}

				Node *successor = this->leafA;
				while(successor->leafB != NULL) successor = successor->leafB;
				pair = successor->pair;
				successor->deleteNode();
			}

			void fix()
			{
				Node *self = this;
				while(self->parent->color == true)
				{	// TODO: What do we do if there is no parent
					if(self->parent->parent->leafB = self->parent)
					{
						if(self->parent->parent->leafA->color == true)
						{
							self->parent->parent->leafA->color = self->parent->color = false;
							self->parent->parent->color = true;
							self = self->parent->parent;
						}
						else
						{
							if(self = self->parent->leafA)
							{
								self = self->parent;
								self->leftRotate();
							}
							self->parent->color = false;
							self->parent->parent->color = true;
							self->rightRotate();
						}
					}
					else
					{
						if(self->parent->parent->leafB->color == true)
						{
							self->parent->parent->leafB->color = self->parent->color = false;
							self->parent->parent->color = true;
							self = self->parent->parent;
						}
						else
						{
							if(self = self->parent->leafB)
							{
								self = self->parent;
								self->rightRotate();
							}
							self->parent->color = false;
							self->parent->parent->color = true;
							self->leftRotate();
						}
					}
				}
			}

			void deleteFix(Node padre) // why not continue the spanish variable names from deleteNode?
			{
				Node *esto = this;
				while(esto != tree || (esto == NULL | color == false))
				{
					if(padre.parent->leafB == esto)
					{
						Node *hermano = padre.parent->leafA;
						if(hermano->color)
						{
							hermano->color = false;
							hermano->parent->color = true;
							hermano->parent->leftRotate();
							hermano = hermano->parent->leafA;
						}

						if((hermano->leafB == NULL || hermano->leafB->color == black) && (hermano->leafA == NULL || hermano->leafA->color == black))
						{
							hermano->color = true;
							esto = hermano->parent;
						}
						else if(hermano->leafA->color == false)
						{
							hermano->leafB->color = false;
							hermano->color = true;
							hermano->rightRotate();
							hermano = hermano->parent->leafA;
						}
						else if(hermano->color == false && hermano->leafA == true)
						{
							hermano->color = hermano->parent->color;
							hermano->parent->color = false;
							hermano->leafA->color = false;
							hermano->parent->leftRotate();
							esto = tree;

						}
					}
					else
					{
						Node *hermano = padre.parent->leafB;
						if(hermano->color)
						{
							hermano->color = false;
							hermano->parent->color = true;
							hermano->parent->leftRotate();
							hermano = hermano->parent->leafB;
						}

						if((hermano->leafB == NULL || hermano->leafB->color == black) && (hermano->leafA == NULL || hermano->leafA->color == black))
						{
							hermano->color = true;
							esto = hermano->parent;
						}
						else if(hermano->leafA->color == false)
						{
							hermano->leafB->color = false;
							hermano->color = true;
							hermano->rightRotate();
							hermano = hermano->parent->leafA;
						}
						else if(hermano->color == false && hermano->leafA == true)
						{
							hermano->color = hermano->parent->color;
							hermano->parent->color = false;
							hermano->leafA->color = false;
							hermano->parent->leftRotate();
							esto = tree;
						}
					}
				}

				esto->color = false;
			}

			void leftRotate()
			{
				Node *x = this;
				Node *y = this->leafA;
				x->leafA = y->leafB;
				if(y->leafB != NULL)
					y->leafB->parent = x;

				y->parent = x->parent;
				if(x->parent == NULL)
					tree = y;
				else if(x == x->parent->leafB)
					x->parent->leafB = y;
				else
					x->parent->leafA = y;
				y->leafB = x;
				x->parent = y;
			}

			void rightRotate()
			{
				Node *x = this;
				Node *y = this->leafB;
				x->leafB = y->leafA;
				if(y->leafA != NULL)
					y->leafA->parent = x;

				y->parent = x->parent;
				if(x->parent == NULL)
					tree = y;
				else if(x == x->parent->leafA)
					x->parent->leafA = y;
				else
					x->parent->leafB = y;
				y->leafA = x;
				x->parent = y;
			}

			Node *parent;
			Node *leafA;
			Node *leafB;
			Pair<K, T> pair;
			bool color; // false is black, true is red
		};

		Node *tree;
		OPERATOR bool eqKey(K k1, K k2)
		{
			if(ExistingOperators<K>::equal) { return k1 == k2; }
			else { return memcmp(&k1, &k2, sizeof(K)) == 0; };
		}

		Node forward(size_t depth)
		{
			tree->traverse(depth);
		}

		public:
		using key_type = K;
		using mapped_type = T;
		using value_type = Pair<const key_type, mapped_type>;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using key_compare = std::less<K>;
		// TODO: More std::map compatablity stuff

		Map()
		{
			tree = new Node();
		}
		Map(const Map &cc)
		{
			tree = new Node(*cc.tree);
		}
		~Map()
		{
			delete tree;
		}
		T &operator[](K key)
		{
			return tree->search(key);
		}

		Option<T&> search(K key)
		{
			T &result = tree->search(key);
			if(engine::errorcode() == ENGINE_INVALID_ARG)
				return Option::none<T&>();
			else
				return Option::some<T&>(result);
		}

		bool has(K key)
		{
			search(key);
			if(engine::errorcode() == ENGINE_INVALID_ARG)
				return false;
			
			return true;
		}

		Option<T&> add(K key, T obj)
		{
			if(*tree == Node())
			{
				*tree = Node(false, Pair<K, T>(key, obj));
				return Option::some<T&>(tree->pair.first);
			}
			else
			{
				T *result = tree->insert(key, obj);
				if(engine::errorcode() == ENGINE_NO_MEM)
					return Option::none<T&>();
				else
				{
					return Option::some<T&>(*result);
				}
			}
		}	

		void rm(K key)
		{
			tree->getNode(key).deleteNode();
		}

		MapIterator<K, T, Compare> begin()
		{
			return { 0, this };
		}

		MapIterator<K, T, Compare> end()
		{
			return { 0, NULL };
		}

		friend template <typename K, typename T> class MapIterator;
	};

	template <typename K, typename T, typename Compare = std::less<K>>
	class MapIterator
	{
		size_t depth;
		Map<K, T, Compare> *map;
		public:
		using difference_type = ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		MapIterator(const MapIterator &cc)
		{
			map = cc.map;
			depth = cc.depth;
		}

		MapIterator()
		{
			depth = 0;
			map = NULL;
		}

		~MapIterator()
		{
			if((uinptr_t)map & 0x8000000000000000 != 0)
				delete ((Map<K, T, Compare>*)((uintptr_t)map & (~0x8000000000000000)));
		}

		MapIterator& operator++()
		{
			depth++;
			return *this;
		}

		MapIterator& operator--()
		{
			depth--;
			return *this;
		}

		T& operator*()
		{
			if(map != NULL)
			{
				if((uinptr_t)map & 0x8000000000000000 != 0)
				{
					engine::errorcode() = ENGINE_INVALID_ARG;
					return ((Map<K, T, Compare>*)((uintptr_t)map & (~Map<K, T, Compare>*)))->forward(depth);
				}
				return map->forward(depth);
			}
			else
			{
				engine::errorcode() = ENGINE_INVALID_ARG;
				map = new Map();
				Node &r = map->forward(depth);
				map = (Map<K, T, Compare>*)((uintptr_t)map | 0x8000000000000000);
			}
		}
	};
};

#endif