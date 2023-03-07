/*
*   name: src/core/gameplayMain.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for gameplayMain()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#define _INTERNALS_ENGINE_THREAD_MAIN_

#include "core/extensions.h"
#include "core/errno.hpp"
#include "core/scene.hpp"
#include "core/scene_int.hpp"
#include "core/component.hpp"
#include "core/Main.hpp"
#include "core/workQueue.hpp"
#include "core/object.hpp"
#include "core/sync.hpp"
#include "core/simd.h"

namespace engine
{
    namespace internals
    {
        workQueue rQueue;
        scene *curScene;
        map<scene, int> scenes;

        // Run the gameplay code
        int gameplayMain()
        {
            // Physics and render lock gameplay
            while(isRenderExecuting.load()) spinlock_pause();
            while(isPhysicsExecuting.load()) spinlock_pause();

            isGameplayExecuting.store(true);
            
            engine::clearErrorcode();

            // TODO: There is probably something we are missing here.

            for(int i = 0; i < curScene->objects.getCount(); i++)
            {
                for(int j = 0; j < curScene->objects[i].cCount; j++)
                {
                    curScene->objects[i].components[j]->update();
                    engine::clearErrorcode();
                }
            }
            
            removeErrorcodeForThread();
            
            isGameplayExecuting.store(false);
        }
    };
};
