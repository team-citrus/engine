/*
*   name: src/physics/init.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for physics::init() and physics::fini()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "physics/physmain.hpp"

using namespace engine;

void internals::physics::Init(bool is2D, Vec3 gravity)
{
	if(is2D)
	{
		internals::physics::state.is2D = true;
		internals::physics::state.stepRate = 30;
		internals::physics::state.gravity2D = physics::Vec2(gravity.x, gravity.y);
		new(&internals::physics::state.world2D) b2World(b2Vec(gravity.x, gravity.y)); // Unfortunately this is necessary
	}
}