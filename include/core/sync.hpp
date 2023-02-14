/*
*   name: include/core/sync.hpp
*   origin: Citrus Engine
*   purpose: Synchronization of the threads
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_SYNCHRONIZATION_HPP__
#define CITRUS_ENGINE_SYNCHRONIZATION_HPP__

namespace engine
{
    namespace internals
    {
        extern bool isPhysicsExecuting;
        extern bool isRenderExecuting;
        extern bool isGameplayExecuting;
    }
}

#endif