/*
*   name: src/physics/collider2d.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for 2D colliders
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <box2d/box2d.h>
#include "physics/physmain.hpp"
#include "physics/collider.hpp"

#define BOX2D(F) ((b2Fixture*)F)

b2PolygonShape convertShapeToB2Shape(engine::physics::Shape &s)
{
	b2PolygonShape shape;
	engine::Vector<engine::physics::Vec2> v;
	for(size_t i = 0; i < s.pointCount(); i++)
	{
		v.push(s[i]);
	}

	shape.Set((b2Vec2*)v.data(), v.getCount());
	return shape;
}

void engine::physics::Collider2D::init()
{
	b2FixtureDef def;
	b2PolygonShape s = convertShapeToB2Shape(shape);

	def.shape = &s;
	def.userData.pointer = (uintptr_t)&getObject();

	def.friction = friction;
	def.restitution = resitituion;
	def.restitutionThreshold = restitutionThreshold;
	def.density = density;
	def.isSensor = isTrigger;
	// TODO: Filter
	fixture = ((b2Body*)rb->body2D)->CreateFixture(&def);
}

void engine::physics::Collider2D::init(Shape s)
{
	b2FixtureDef def;
	b2PolygonShape b2S = convertShapeToB2Shape(s);

	def.shape = b2S;
	def.userData.pointer = (uintptr_t)&getObject();

	def.friction = friction;
	def.restitution = resitituion;
	def.restitutionThreshold = restitutionThreshold;
	def.density = density;
	def.isSensor = isTrigger;
	// TODO: Filter
	fixture = ((b2Body*)rb->body2D)->CreateFixture(&def);
}

void engine::physics::Collider2D::setTriggerStatus(bool t)
{
	isTrigger = t;

	if(fixture != NULL)
	{
		BOX2D(fixture)->SetSensor(t);
	}
}
bool engine::physics::Collider2D::getTriggerStatus() const
{
	if(fixture != NULL)
	{
		return BOX2D(fixture)->IsSensor();
	}

	return isTrigger;
}

void engine::physics::Collider2D::setDensity(float d)
{
	density = d;

	if(fixture != NULL)
	{
		BOX2D(fixture)->SetDensity(d);
	}
}
float engine::physics::Collider2D::getDensity() const
{
	return (fixture == NULL) ? density : BOX2D(fixture)->GetDensity();
}

void engine::physics::Collider2D::setFriction(float f)
{
	friction = f;

	if(fixture != NULL)
	{
		BOX2D(fixture)->SetFriction(f);
	}
}
float engine::physics::Collider2D::getFriction() const
{
	return (fixture == NULL) ? friction : BOX2D(fixture)->GetFriction();
}

void engine::physics::Collider2D::setRestitution(float r)
{
	restitution = r;

	if(fixture != NULL)
	{
		BOX2D(fixture)->SetRestitution(r);
	}
}
float engine::physics::Collider2D::getRestitution() const
{
	return (fixture == NULL) ? restitution : BOX2D(fixture)->GetRestitution();
}

void engine::physics::Collider2D::setRestitution(float t)
{
	restitutionThreshold = t;

	if(fixture != NULL)
	{
		BOX2D(fixture)->SetRestitutionThreshold(t);
	}
}
float engine::physics::Collider2D::getRestitutionThreshold() const
{
	return (fixture == NULL) ? restitutionThreshold : BOX2D(fixture)->GetRestitutionThreshold();
}