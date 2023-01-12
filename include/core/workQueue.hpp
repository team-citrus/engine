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
	};
};

#endif