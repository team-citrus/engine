/*
*   name: src/core/step.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for step()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#define _INTERNALS_ENGINE_THREAD_MAIN_
#include "physics/physmain.hpp"
#include "core/scene.hpp"
#include "core/scene_int.hpp"
#include "core/component.hpp"
#include "core/Main.hpp"
#include "core/sync.hpp"
#include "core/simd.h"
#define __CITRUS_ENGINE_SOURCE_FILE__

using namespace engine;

int internals::physics::step()
{
	if(internals::physics::state.is2D)
	{
		internals::physics::state.world2D.step(1.0f/(float)internals::physics::state.stepRate, 8, 3); // TODO: Configurable solvers
	}
	else
	{
		internals::physics::state.world3D.stepSimulation(btScalar(1.0f/(float)internals::physics::state.stepRate), 1, btScalar(1.0f/(float)internals::physics::state.stepRate));
	}
}

void internals::physics::b2Listener::BeginContact(b2Contact *thingy) override
{
	internals::physics::b2Listener::ContactJob cj;
	cj.ptr = thingy;
	cj.enterOrExit = true;
	if(internals::usrThreads > internals::engineThreads)
	{
		cj.schedule();
		cj.ASAP();
	}
	else
	{
		cj.sysSchedule();
	}
}