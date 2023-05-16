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

#define BOX2D(F) ((b2Body*)F)

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

	bodyDef.allowSleep = true;
	bodyDef.awake = true;
	bodyDef.bullet = bullet;
	bodyDef.enabled = enabled;

	bodyDef.gravityScale = gravityScale;
	bodyDef.userData.pointer = (uintptr_t)&getObject();

	body2D = (void*)engine::internals::physics::state.world2D->CreateBody(&bodyDef);
}

Vec2 engine::physics::Rigidbody2D::getCenterOfMass() const
{
	if(body2D == NULL)
	{
		return trans->position;
	}

	return BOX2D(body2D)->GetWorldCenter();
}

Vec2 engine::physics::Rigidbody2D::getCenterOfMass() const
{
	if(body2D == NULL)
	{
		return Vec2(0, 0);
	}

	return BOX2D(body2D)->GetLocalCenter();
}

void engine::physics::Rigidbody2D::setVelocity(Vec2 vel)
{
	if(body2D != NULL)
	{
		bVec2 v(vel.x, vel.y);
		BOX2D(body2D)->SetLinearVelocity(v);
	}
}

Vec2 engine::physics::Rigidbody2D::getVelocity() const
{
	if(body2D == NULL) 
		return Vec2(0, 0);

	bVec2 v = BOX2D(body2D)->GetLinearVelocity();
	return Vec2(v.x, v.y);
}

void engine::physics::Rigidbody2D::setAngularVelocity(float omeha)
{
	if(body2D != NULL)
	{
		BOX2D(body2D)->SetAngularVelocity(omega);
	}
}

float engine::physics::Rigidbody2D::getAngularVelocity()
{
	return (body2D == NULL) ? 0 : BOX2D(body2D)->GetAngularVelocity;
}

void engine::physics::Rigidbody2D::applyForce(const Vec2 force, bool wake, int type)
{
	if(force == Vec2(0, 0))
	{
		return;
	}

	if(body2D != NULL)
	{
		switch(type)
		{
			case RB_FORCEMODE_FORCE:
			BOX2D(body2D)->ApplyForceToCenter(*(b2Vec2*)&force, wake);
			return;

			case RB_FORCEMODE_IMPULSE:
			BOX2D(body2D)->ApplyLinearImpulseToCenter(*(b2Vec2*)&force, wake);
			return;

			// TODO: rest of this function
		}
	}
}

void engine::physics::Rigidbody2D::applyForce(const Vec2 force, const Vec2 point, bool wake, int type)
{
	if(force == Vec2(0, 0))
	{
		return;
	}

	if(body2D != NULL)
	{
		switch(type)
		{
			case RB_FORCEMODE_FORCE:
			BOX2D(body2D)->ApplyForce(*(b2Vec2*)&force, *(b2Vec2*)&point, wake);
			return;

			case RB_FORCEMODE_IMPULSE:
			BOX2D(body2D)->ApplyLinearImpulse(*(b2Vec2*)&force, *(b2Vec2*)&point, wake);
			return;

			// TODO: rest of this function
		}
	}
}

float engine::physics::Rigidbody2D::getMass() const
{
	if(body2D == NULL)
		return -1f;

	return BOX2D(body2D)->GetMass());
}

float engine::physics::Rigidbody2D::getLinearDamping() const
{
	if(body2D == NULL)
		return linearDamping;

	return BOX2D(body2D)->GetLinearDamping();
}

void engine::physics::Rigidbody2D::setLinearDamping(float f)
{
	if(body2D != NULL)
	{
		BOX2D(body2D)->SetLinearDamping(f);
	}

	linearDamping = f;
}

float engine::physics::Rigidbody2D::getAngularDamping() const
{
	if(body2D == NULL)
		return linearDamping;

	return BOX2D(body2D)->GetLinearDamping();
}

void engine::physics::Rigidbody2D::setAngularDamping(float f)
{
	if(body2D != NULL)
	{
		BOX2D(body2D)->SetLinearDamping(f);
	}

	linearDamping = f;
}

float engine::physics::Rigidbody2D::getScaleOfGravity() const
{
	if(body2D == NULL)
		return gravityScale;

	return BOX2D(body2D)->GetGravityScale();
}

void engine::physics::Rigidbody2D::setLinearDamping(float f)
{
	if(body2D != NULL)
	{
		BOX2D(body2D)->SetGravityScale(f);
	}

	gravityScale = f;
}

void engine::physics::Rigidbody2D::setType(int t)
{
	if(body != NULL)
	{
		BOX2D(body2D)->SetType((b2BodyType)t);
	}

	type = t;
}

int engine::physics::Rigidbody2D::getType() const
{
	return type;
}

void engine::physics::Rigidbody2D::setBullet(bool b)
{
	if(body != NULL)
	{
		BOX2D(body2D)->SetBullet(b);
	}

	bullet = b;
}

bool engine::physics::Rigidbody2D::isBullet()
{
	return bullet;
}

void engine::physics::Rigidbody2D::wake()
{
	if(body != NULL)
		BOX2D(body2D)->SetAwake(true);
}

void engine::physics::Rigidbody2D::sleep()
{
	if(body != NULL)
		BOX2D(body2D)->SetAwake(false);
}

bool engine::physics::Rigidbody2D::isAwake() const
{
	if(body != NULL)
		return BOX2D(body2D)->IsAwake();

	return false;
}

void engine::physics::Rigidbody2D::enable()
{
	if(body != NULL)
		BOX2D(body2D)->SetEnabled(true);
}

void engine::physics::Rigidbody2D::disable()
{
	if(body != NULL)
		BOX2D(body2D)->SetEnabled(false);
}

bool engine::physics::Rigidbody2D::isEnabled() const
{
	if(body != NULL)
		return BOX2D(body2D)->IsEnabled();

	return false;
}

void engine::physics::Rigidbody2D::lockRotation()
{
	if(body != NULL)
		BOX2D(body2D)->SetFixedRotation(true);

	fixedRotation = true;
}

void engine::physics::Rigidbody2D::unlockRotation()
{
	if(body != NULL)
		BOX2D(body2D)->SetFixedRotation(false);

	fixedRotation = false;
}

bool engine::physics::Rigidbody2D::isRotationLocked() const
{
	if(body != NULL)
		return BOX2D(body2D)->IsFixedRotation();

	return fixedRotation;
}