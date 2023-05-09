/*
*   name: src/core/step.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for step()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "physics/physmain.hpp"
#include "core/scene.hpp"
#include "core/scene_int.hpp"
#include "core/component.hpp"
#include "core/Main.hpp"
#include "core/sync.hpp"
#include "core/simd.h"
#define __CITRUS_ENGINE_SOURCE_FILE__

int engine::internals::physics::step()
{
	if(engine::internals::physics::state.is2D)
	{
		engine::internals::physics::state.world2D.step(1.0f/(float)engine::internals::physics::state.stepRate, 8, 3); // TODO: Configurable solvers
	}
	else
	{
		engine::internals::physics::state.world3D.stepSimulation(btScalar(1.0f/(float)engine::internals::physics::state.stepRate), 1, btScalar(1.0f/(float)engine::internals::physics::state.stepRate));
	}
}