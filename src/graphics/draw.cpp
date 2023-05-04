/*
*   name: src/graphics/draw.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for the draw()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#include <vulkan.h>
#include <atomic>
#include "core/errno.hpp"
#include "core/Main.hpp"
#include "core/sync.hpp"
#include "core/extensions.h"
#include "core/simd.h"

NEVER_INLINE
int engine::internals::Vulkan::vkDraw()
{
	while(engine::internals::isRenderBlocked.load()) spinlock_pause();
	
	engine::clearErrorcode();

	// OK basic render process for 3D goes as follows:
	// Gather a list of everything we have to render, as objects, to make shader access quicker
	// Parse together a list of all the shader stages and what not
	// Handle all the overhead of Vulkan
	// Handle GUI somehow, possibly integrate it into Vulkan rendering
	// Give Vulkan the orders
	// Cleanup
	// And the rendering for 2D:
	// Exact same as 3D
	
	// TODO: Frame buffer stuff
	
	removeErrorcodeForThread();
			
	physicsJustExecuted.store(false);
	renderJustExecuted.store(true);
	gameplayJustExecuted.store(false);
	isRenderBlocked.store(true);
			
	if(gameplayJustExecuted.load())
	{
		isPhysicsBlocked.store(false);
	}
	else
	{
		isGameplayBlocked.store(false);
	}
}