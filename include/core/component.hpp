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
#include "include/core/extensions.hpp"
#include "include/core/object.hpp"

namespace engine
{
	// The base class for all componenets, similar to Unity components
	class component
	{
		public:
			// Functions similar to Unity's awake()
			virtual void awake();
			// Functions similar to Unity's start()
			virtual void start();
			// Functions similar to Unity's update()
			virtual void update();
			
			// Functions similar to Unity's fixedUpdate()
			virtual void fixedUpdate();
			// Functions similar to Unity's onTriggerEnter()
			virtual void onTriggerEnter();
			// Functions similar to Unity's onTriggerStay()
			virtual void onTriggerStay();
			// Functions similar to Unity's onTriggerExit()
			virtual void onTriggerExit();

			OPERATOR object &getObject()
			{
				return *owner;
			}

			// Functions like Unity's getComponent<T>()
			template <typename T>
			OPERATOR T &getComponent()
			{
				return owner->getComponet();
			}
		private:
			object *owner;
			size_t size;

			// Use this to validate component type
			std::type_info componentID;
			friend class object;
	};
};

#endif