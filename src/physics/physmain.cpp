/*
*   name: src/core/physmain.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for physmain()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

// physmain.cpp is an exception to the no STL rule
#include <chrono>
#include <mutex>
#include "physics/physmain.hpp"
#include "core/scene.hpp"
#include "core/scene_int.hpp"
#include "core/component.hpp"
#include "core/Main.hpp"
#include "core/sync.hpp"
#include "core/simd.h"

#define getTimeInMils() std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
extern void waitms(size_t mils);

namespace engine
{
    namespace internals
    {
        int physmain()
        {
            while(!loadNecesary)
            {
                while(internals::physics::state.stepRate == 0) spinlock_pause();
                while(isRenderExecuting.load()) spinlock_pause();
                while(isGameplayExecuting.load()) spinlock_pause();

                isPhysicsExecuting.store(true);
                size_t phystart = getTimeInMils();
                
                internals::physics::step();
                
                // TODO: Trigger stuff

                isPhysicsExecuting.store(false);
                internals::physics::physicsDur = getTimeInMils() - phystart;
                waitms(
                    (internals::physics::physicsDelta = (1000 - (internals::physics::physicsDur * internals::physics::state.stepRate))/internals::physics::state.stepRate)
                );
            }

            for(int i = 0; i < internals::curScene->objects.getCount(); i++)
            {
                internals::curScene->objects[i].~object();
            }
            curScene->objects.~Vector();

            curScene = &scenes.lookup(currentScene);
            curScene->constructor();
        }
    }
}