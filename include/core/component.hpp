/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
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