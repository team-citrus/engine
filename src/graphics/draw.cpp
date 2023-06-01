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

#define WASTE_60_CPU_CYCLES asm volatile( \
		// Wasted 3 + 1 = 4 cycles
		"xor %r8, %r8;" \
		// Wastes 2(3 + 1) = 8 cycles a piece
		// 12 cycles wasted.
		"shl $1, %r8;" \
		"shr $1, %r8;" \
		// 20 cycles wasted.
		"shl $1, %r8;" \
		"shr $1, %r8;" \
		// 28 cycles wasted
		"shl $1, %r8;" \
		"shr $1, %r8;" \
		// 36 cycles wasted
		"shl $1, %r8;" \
		"shr $1, %r8;" \
		// 44 cycles wasted
		"shl $1, %r8;" \
		"shr $1, %r8;" \
		// 52 cycles wasted
		"shl $1, %r8;" \
		"shr $1, %r8;" \
		// 60 cycles wasted
		"shl $1, %r8;" \
		"shr $1, %r8;" \
	)

static ALWAYS_INLINE void waste1920CPUCycles()
{
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
	WASTE_60_CPU_CYCLES;
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
		waste2000CPUCycles();
	}
}