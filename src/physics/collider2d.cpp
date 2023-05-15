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