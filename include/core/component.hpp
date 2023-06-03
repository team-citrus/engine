/*
*   name: include/core/component.hpp
*   origin: Citrus Engine
*   purpose: Provide the base class for all components
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPONENTS_HPP__
#define CITRUS_ENGINE_COMPONENTS_HPP__

#include <typeinfo>
#include "../core/extensions.h"
#include "../core/object.hpp"

namespace engine // TODO: Internalize some of this stuff
{
	typedef void (*ComponentFuncPtr)(void*);
	
	// The base class for all components, similar to Unity components
	class Component
	{
		public:
			Component()
			{
				return;
			}

			// Functions similar to Unity's awake()
			virtual void awake()
			{
				return;
			}
			// Functions similar to Unity's start()
			virtual void start()
			{
				return;
			}
			// Functions similar to Unity's update()
			virtual void update()
			{
				return;
			}
			
			// Functions similar to Unity's fixedUpdate()
			virtual void fixedUpdate()
			{
				return;
			}
			
			// Exists for obvious reasons.
			virtual ~Component()
			{
				return;
			}

			virtual void destroy()
			{
				return;
			}

			OPERATOR Object &getObject()
			{
				return *owner;
			}
		private:
			Object *owner;

		protected:
			// Use this to validate component type
			virtual std::type_info getComponentID();
			friend class Object;
	};
};

#endif
