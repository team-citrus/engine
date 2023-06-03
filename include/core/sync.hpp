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

extern MUTEX std::atomic_bool isGameplayExecuting;
extern MUTEX std::atomic_bool isRenderExecuting;

extern MUTEX std::atomic_uint32_t objectCtr;
extern MUTEX std::atomic_uint32_t objectCnt;

#endif