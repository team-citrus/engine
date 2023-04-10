/*
*   name: src/core/physmain.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for physmain()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#define __CITRUS_ENGINE_SOURCE_FILE__

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
            engine::clearErrorcode();
            while(!loadNecesary)
            {
                while(internals::physics::state.stepRate == 0) spinlock_pause();
                while(isPhysicsBlocked.load()) spinlock_pause();
                isRenderBlocked.store(true);
				isGameplayBlocked.store(true);
                size_t phystart = getTimeInMils();
                
                internals::physics::step();
                
                // TODO: Trigger stuff

                isRenderBlocked.store(false);
				isGameplayBlocked.store(false);
				physicsJustExecuted.store(true);
				renderJustExecuted.store(false);
				gameplayJustExecuted.store(false);
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