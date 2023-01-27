/*
*   name: include/core/object.hpp
*   origin: Citrus Engine
*   purpose: Provide the engine::object class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OBJECTS_HPP__
#define CITRUS_ENGINE_OBJECTS_HPP__

#include <cstdint>
#include <cstring>
#include "core/extensions.hpp"
#include "core/component.hpp"
#include "core/mem.hpp"
#include "core/Main.hpp"

namespace engine
{
	class object
	{
		public:
			object()
			{
				cCount = 0;
				components = (component**)memalloc(sizeof(component*), MEM_FLAG_UNIT_BYTE);
			}
			// Functions like Unity's AddComponent<T>()
			template<typename T>
			T &addComponent()
			{
				componentCount++;
				components = memrealloc(components, sizeof(component*) * componentCount, MEM_FLAG_UNIT_BYTE);
				components[componentCount - 1]->awake();
				return *components[componentCount - 1];
			}

			// Functions like Unity's GetComponent<T>()
			template<typename T>
			OPERATOR T &getComponent()
			{
				for(int i = 0; i < componentCount; i++)
					if(components[i]->componentID == typeid(T))
						return *components[i];
			}

			// Functions like Unity's hasComponent<T>()
			template<typename T>
			OPERATOR bool hasComponent()
			{
				for(int i = 0; i < componentCount; i++)
					if(components[i]->componentID == typeid(T))
						return true;
				return false;
			}

			OPERATOR bool hasTag(const char *tag)
			{
				for(int i = 0; i < tags.getCount(); i++)
				{
					if(!strcmp(tags[i], tag))
					{
						return true;
					}
				}
				return false;
			}

			OPERATOR void addTag(const char *tag)
			{
				tags.push(tag);
			}

			OPERATOR int componentCount()
			{
				return cCount;
			}
		private:
			Vector<const char*> tags;
			int cCount;
			component **components;

			friend int internals::gameplayMain();
	};

	// TODO: Rust interop class
};

#endif