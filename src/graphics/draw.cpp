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

void waitms(size_t mils)
{
	#ifdef CITRUS_ENGINE_UNIX

	timespec t = { 0, (long)(mils * 1000000l) };
	nanosleep(&t, NULL); // Doesn't matter if we don't sleep long enough, waitms() is only to make sure we yield to the OS

	#else 

	Sleep(mils); // Rare instance of the Windows version being easier than the POSIX version

	#endif
}

static ALWAYS_INLINE void waste100CPUCycles()
{
	asm volatile(
		// Wastes 15 cycles a piece, ideally

		// 15 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
		"mov %rax, %rcx;"
		// 30 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
		"mov %rax, %rcx;"
		// 45 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
		"mov %rax, %rcx;"
		// 60 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
		"mov %rax, %rcx;"
		// 75 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
		"mov %rax, %rcx;"
		// 90 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
		"mov %rax, %rcx;"
		// 100 cycles wasted
		"mov %r8, %r9;"
		"mov %r10, %r11;"
	)
}

NEVER_INLINE
int engine::internals::Vulkan::vkDraw()
{
	engine::clearErrorcode();
	while(true)
	{
		while(isGameplayExecuting.load())
		{
			if(objectCtr != 0 && objectCnt != 0 && (float)objectCtr/(float)objectCnt < .75)
				waitms(5);
			else
				spinlock_pause();
		}
		isRenderExecuting.store(true);

		// TODO: somewhat framerate.

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

		isRenderExecuting.store(false);
		waste100CPUCycles();
	}
}