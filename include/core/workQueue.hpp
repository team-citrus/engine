/*
*   name: include/core/workQueue.hpp
*   origin: Citrus Engine
*   purpose: Provides work queues, pretty much just vectors of function pointers, meant to improve code readability of code in event loop functions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_CORE_WORK_QUEUES_HPP__
#define CITRUS_ENGINE_CORE_WORK_QUEUES_HPP__

#include "core/extensions.hpp"
#include "core/vector.hpp"

namespace engine
{
	namespace internals
	{
		typedef size_t (*queuePtr)(...);
		typedef Vector<queuePtr> workQueue;
		
		template <typename...A>
		OPERATOR size_t executeItemInQueue(queuePtr ptr, A...args)
		{
			return ptr(args...);
		}

		/*	Executes all items in a queue, applying all args passed to each of the items in the queue
		*	@return Vector of each of the returns
		*/
		template <typename...A>
		OPERATOR Vector<size_t> executeQueue(workQueue queue, A...args)
		{
			Vector<size_t> ret;
			for(int i = 0; i < queue.getCount(); i++)
				ret.push(executeItemInQueue(queue[i], args...));
			return ret;
		}
	};
};

#endif