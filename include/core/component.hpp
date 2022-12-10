#ifndef CITRUS_ENGINE_COMPONENTS_HPP__
#define CITRUS_ENGINE_COMPONENTS_HPP__

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

	/*	TODO: add engine::object
	*		engine::object &getObject();
	*
	*	private:
	*		engine::object *owner
	*/
	};
};

#endif