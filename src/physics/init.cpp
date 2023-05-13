/*
*   name: src/physics/init.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for physics::init() and physics::fini()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "physics/physmain.hpp"

using namespace engine;

void internals::physics::Init(bool is2D, engine::physics::Vec3 gravity)
{
	if(is2D)
	{
		internals::physics::state.is2D = true;
		internals::physics::state.stepRate = 30;
		internals::physics::state.gravity2D = engine::physics::Vec2(gravity.x, gravity.y);
		b2Vec2 v(gravity.x, gravity.y);
		
		internals::physics::state.world2D = new b2World(v); // Unfortunately this is necessary
	}
}