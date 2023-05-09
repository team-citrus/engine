/*
*   name: include/core/sync.hpp
*   origin: Citrus Engine
*   purpose: Synchronization of the threads
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_SYNCHRONIZATION_HPP__
#define CITRUS_ENGINE_SYNCHRONIZATION_HPP__

#include <atomic>
#include "../core/extensions.h"

namespace engine
{
	namespace internals
	{
		extern MUTEX std::atomic_bool isPhysicsBlocked;
		extern MUTEX std::atomic_bool isRenderBlocked;
		extern MUTEX std::atomic_bool isGameplayBlocked;

		extern MUTEX std::atomic_bool physicsJustExecuted;
		extern MUTEX std::atomic_bool renderJustExecuted;
		extern MUTEX std::atomic_bool gameplayJustExecuted;
	}
}

#endif