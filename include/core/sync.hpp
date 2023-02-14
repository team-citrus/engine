/*
*   name: include/core/sync.hpp
*   origin: Citrus Engine
*   purpose: Synchronization of the threads
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_SYNCHRONIZATION_HPP__
#define CITRUS_ENGINE_SYNCHRONIZATION_HPP__

#include "core/extensions.h"

namespace engine
{
    namespace internals
    {
        extern MUTEX bool isPhysicsExecuting;
        extern MUTEX bool isRenderExecuting;
        extern MUTEX bool isGameplayExecuting;
    }
}

#endif