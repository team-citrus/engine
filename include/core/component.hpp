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
#include "core/extensions.h"
#include "core/object.hpp"
#include "physics/collider.hpp"

namespace engine // TODO: Internalize some of this stuff
{
	typedef void (*componentFuncPtr)(void*);
	typedef void (*triggerFuncPtr)(void*, collider*, collider*)
		
	// Exactly like it's Rust counterpart
	struct rustComponentBase
	{
		componentFuncPtr awake;
		componentFuncPtr start;
		componentFuncPtr update;
		componentFuncPtr fixedUpdate;
		triggerFuncPtr onTriggerEnter;
		triggerFuncPtr onTriggerStay;
		triggerFuncPtr onTriggerExit;
	};
	
	// The base class for all components, similar to Unity components
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
			virtual void onTriggerEnter(collider *offender, collider *victim)
			{
				return;
			}
			// Functions similar to Unity's onTriggerStay()
			virtual void onTriggerStay(collider *offender, collider *victim)
			{
				return;
			}
			// Functions similar to Unity's onTriggerExit()
			virtual void onTriggerExit(collider *offender, collider *victim)
			{
				return;
			}
			
			// Exists for obvious reasons.
			virtual ~component()
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

	// Wrapper around Rust components, unfortunately C++ can't add or see into Rust components, not without copius amounts of Jerryrigging
	class rustComponent : component
	{
		public:
		// Pointer to the actual component. Please note that actual Rust components can only be added from Rust
		rustComponentBase *base; // TODO: Fix that
		
		void awake() override
		{
			base->awake(base);
		}
		
		void start() override
		{
			base->start(base);
		}
		
		void update() override
		{
			base->update(base);
		}
		
		void fixedUpdate() override
		{
			base->fixedUpdate(base);
		}

	 	void onTriggerEnter(collider *offender, collider *victim) override
		{
			base->onTriggerEnter(base, offender, victim);
		}

		void onTriggerStay(collider *offender, collider *victim) override
		{
			base->onTriggerStay(base, offender, victim);
		}
		
		void onTriggerExit(collider *offender, collider *victim) override
		{
			base->onTriggerExit(base, offender, victim);
		}
	}
};

#endif
