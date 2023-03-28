/*
*   name: include/core/Object.hpp
*   origin: Citrus Engine
*   purpose: Provide the engine::Object class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OBJECTS_HPP__
#define CITRUS_ENGINE_OBJECTS_HPP__

#include <cstdint>
#include <cstring>
#include "core/extensions.h"
#include "core/component.hpp"
#include "core/mem.hpp"
#include "core/Main.hpp"
#include "core/hash.hpp"
#include "core/vector.hpp"

namespace engine
{
	class Object
	{	// TODO: More stuff
		public:
			OPTIMIZE(3) Object()
			{
				cCount = 0;
				components = (component**)memalloc(sizeof(component*));
			}

			OPTIMIZE(3) ~Object()
			{
				for(size_t i = 0; i < cCount; i++)
				{
					components[i]->~component();
				}

				memfree(components);
			}

			// Functions like Unity's AddComponent<T>()
			OPTIMIZE(3) template<typename T>
			T &addComponent()
			{
				componentCount++;
				components = memrealloc(components, sizeof(component*) * componentCount);
				components[componentCount - 1]->awake();
				return *components[componentCount - 1];
			}

			// Functions like Unity's GetComponent<T>()
			OPTIMIZE(3) template<typename T>
			T &getComponent()
			{
				for(int i = 0; i < componentCount; i++)
					if(components[i]->componentID == typeid(T))
						return *components[i];
			}

			// Functions like Unity's hasComponent<T>()
			OPTIMIZE(3) template<typename T>
			OPERATOR bool hasComponent()
			{
				for(int i = 0; i < componentCount; i++)
					if(components[i]->componentID == typeid(T))
						return true;
				return false;
			}

			OPTIMIZE(3) OPERATOR bool hasTag(const char *tag)
			{
				hash_t h = hash(tag, strlen(tag));
				for(int i = 0; i < tags.getCount(); i++)
					if(tags[i] == tag)
						return true;
				return false;
			}

			OPTIMIZE(3) OPERATOR void addTag(const char *tag)
			{
				tags.push(hash(tag, strlen(tag)));
			}

			OPTIMIZE(3) OPERATOR int componentCount()
			{
				return cCount;
			}

			#ifdef _INTERNALS_ENGINE_THREAD_MAIN_

			OPTIMIZE(3) OPERATOR Vector<component*> getComponents()
			{
				return Vector<component*>(components, cCount);
			}

			#endif
		private:
			Vector<hash_t> tags;
			int cCount;
			Component **components;
	};

	// TODO: Rust interop class
};

#endif
