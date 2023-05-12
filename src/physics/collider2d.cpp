/*
*   name: src/physics/collider2d.cpp
*   origin: Citrus Engine
*   purpose: Provides the code for 2D colliders
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <box2d/box2d.h>
#include "physics/collider.hpp"

void engine::physics::Collider2D::init()
{
	b2FixtureDef def;
	// TODO: SHAPE
	def.userData.pointer = &getObject();

	def.friction = friction;
	def.restitution = resitituion;
	def.restitutionThreshold = restitutionThreshold;
	def.density = density;
	def.isSensor = isTrigger;
	// TODO: Filter
	fixture = ((b2Body*)rb.body2D)->CreateFixture(&def);
}