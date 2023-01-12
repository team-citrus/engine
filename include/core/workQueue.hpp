/*
*   name: include/core/workQueue.hpp
*   origin: Citrus Engine
*   purpose: Provides work queues, pretty much just vectors of function pointers, meant to improve code readability of code in event loop functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_CORE_WORK_QUEUES_HPP__
#define CITRUS_ENGINE_CORE_WORK_QUEUES_HPP__

#include "include/core/extensions.hpp"
#include "include/core/vector.hpp"

namespace engine
{
	namespace internals
	{
		typedef size_t (*queuePtr)(...);
		typedef Vector<queuePtr> workQueue;
		
		#define EXECUTE_ITEM_IN_QUEUE(x, ...) (__VA_ARGS_FIX__((queuePtr)x(__VA_ARGS__)))

		/*	Executes all items in a queue, applying all args passed to each of the items in the queue
		*	@return Vector of each of the returns
		*/
		template <typename...A>
		Vector<size_t> executeQueue(Vector<queuePtr> queue, A...args)
		{
			Vector<size_t> ret;
			for(int i = 0; i < queue.getCount(); i++)
				ret.push(EXECUTE_ITEM_IN_QUEUE(queue[i], args...));
			return ret;
		}
	};
};

#endif