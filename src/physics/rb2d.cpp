/*
*   name: src/physics/rb2d.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for 2D rigidbodies
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#include "physics/physmain.hpp"
#include "core/object.hpp"
#include "core/transform.hpp"
#include "physics/rigidbody.hpp"

int engine::physics::Rigidbody2D::init() override
{
	if(inited)
		return;
	
	inited = true;
	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(t.position.x, t.position.y);
	bodyDef.angle = t.rotation;

	bodyDef.linearDamping = linearDamping;
	bodyDef.angularDamping = angularDamping;

	bodyDef.allowSleep = allowSleep;
	bodyDef.awake = awake;
	bodyDef.bullet = bullet;
	bodyDef.enabled = enabled;

	bodyDef.gravityScale = gravityScale;
	bodyDef.userData.pointer = (uintptr_t)&getObject();

	body2D = (void*)engine::internals::physics::state.CreateBody(&bodyDef);
}