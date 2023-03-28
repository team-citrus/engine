/*
*   name: include/physics/rigidbody.hpp
*   origin: Citrus Engine
*   purpose: Provides the engine::physics::rigidbody class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_RIGIDBODIES_HPP__
#define CITRUS_ENGINE_RIGIDBODIES_HPP__

#include <btBulletDynamicsCommon.h>
#include <box2d/box2d.h>
#include "core/extensions.h"
#include "physics/vectors.hpp"
#include "physics/physobject.hpp"

#define RB_FORCEMODE_IMPULSE 0
#define RB_FORCEMODE_FORCE 1
#define RB_FORCEMODE_ACCELERATION 2
#define RB_FORCEMODE_VELOCITY 3

#define RB_AWAKE true
#define RB_ASLEEP false

namespace engine
{
	namespace physics
	{
		class Rigidbody2D : Component
		{
			private:
				// Box2d rigidbody representation
				b2Body *body2D;

				Physobject2D *owner;

				// See if we should keep calculating it, or not. Useful for optimization
				bool awake;
			public:
				// Constructors
				Rigidbody2D();

				// Rigidbody stuff

				// Awakes the rigidbody if it's asleep
				void awaken();

				// Get sleep status
				bool isAwake();

				// Forces

				/*	Practically identical to Unity's Rigidbody.AddForce()
				*	@param force The force to apply, based on coordinates
				*	@param mode The mode of the force
				*/
				void applyForce(Vec2 force, int mode);

				// Velocity

				// Gets the velocity in the form of a Vec2
				Vec2 getVelocity();

				/*	Sets the velocity
				*	@param velocity The new velocity
				*/
				void setVelocity(Vec2 velocity);

				// Advanced physics stuff
				
				//	Gets the owner
				OPERATOR Physobject2D &getPhysobject()
				{
					return *owner;
				}
		};

		class Rigidbody3D : Component
		{
			private:
				// Box2d rigidbody representation
				btRigidBody *body3D;

				Physobject3D &owner;

				// See if we should keep calculating it, or not. Useful for optimization
				bool awake;
			public:
				// Constructors
				Rigidbody3D();

				// Rigidbody stuff

				// Awakes the rigidbody if it's asleep
				void awaken();

				// Get sleep status
				bool isAwake();

				// Forces

				/*	Practically identical to Unity's Rigidbody.AddForce()
				*	@param force The force to apply, based on coordinates
				*	@param mode The mode of the force
				*/
				void applyForce(Vec3 force, int mode);

				// Velocity

				// Gets the velocity in the form of aVec3
				Vec3 getVelocity();

				/*	Sets the velocity
				*	@param velocity The new velocity
				*/
				void setVelocity(Vec3 velocity);

				// Advanced physics stuff
				
				//	Gets the owner
				OPERATOR Physobject3D &getPhysobject()
				{
					return *owner;
				}
		};
	}
}

#endif