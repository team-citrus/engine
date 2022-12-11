#ifndef CITRUS_ENGINE_COMPONENTS_HPP__
#define CITRUS_ENGINE_COMPONENTS_HPP__

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

			object &getObject();

			// Functions like Unity's getComponent<T>()
			template <typename T>
			T &getComponent();
		private:
			object *owner;
			size_t size;

			friend class object;
	};
};

#endif