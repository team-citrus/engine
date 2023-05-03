/*
*   name: src/core/gameplayMain.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for gameplayMain()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#define _INTERNALS_ENGINE_THREAD_MAIN_
#define __CITRUS_ENGINE_SOURCE_FILE__

#ifdef _WIN32
#include <Windows.h>
#endif

#include <cstring>
#include "core/input.hpp"
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
		WorkQueue rQueue;
		scene *curScene;
		Map<scene, int> scenes;

		// Run the gameplay code
		NEVER_INLINE int gameplayMain()
		{
			// Physics and render lock gameplay
			while(isGameplayBlocked.load()) spinlock_pause();
			isRenderBlocked.store(true);
			isPhysicsBlocked.store(true);
			
			engine::clearErrorcode();

			#ifdef _WIN32

			// Input system stuff
			memcpy(prevInput, currentInput, 256);
			GetKeyboardState(currentInput);

			#else

			// TODO: XLib stuff.

			#endif

			// TODO: There is probably something we are missing here.

			for(int i = 0; i < curScene->objects.getCount(); i++)
			{
				vec<Component*> components = curScene->objects[i].getComponents();
				for(int j = 0; j < components.getCount(); j++)
				{
					components[j]->update();
					engine::clearErrorcode();
				}
			}
			
			removeErrorcodeForThread();
			
			physicsJustExecuted.store(false);
			renderJustExecuted.store(false);
			gameplayJustExecuted.store(true);
			isGameplayBlocked.store(true);
			
			if(renderJustExecuted.load())
			{
				isPhysicsBlocked.store(false);
			}
			else
			{
				isRenderBlocked.store(false);
			}
		}
	};
};
