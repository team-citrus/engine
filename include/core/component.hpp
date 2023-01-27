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
#include "core/extensions.hpp"
#include "core/object.hpp"

namespace engine
{
	// The base class for all componenets, similar to Unity components
	class component
	{
		public:
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
			// Functions similar to Unity's onTriggerEnter()
			virtual void onTriggerEnter()
			{
				return;
			}
			// Functions similar to Unity's onTriggerStay()
			virtual void onTriggerStay()
			{
				return;
			}
			// Functions similar to Unity's onTriggerExit()
			virtual void onTriggerExit()
			{
				return;
			}

			OPERATOR object &getObject()
			{
				return owner;
			}
		private:
			object &owner;

			// Use this to validate component type
			std::type_info componentID;
			friend class object;
	};
};

#endif