/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_RIGIDBODIES_HPP__
#define CITRUS_ENGINE_RIGIDBODIES_HPP__

#include <btBulletDynamicsCommon.h>
#include <box2d/box2d.h>
#include "include/core/extensions.hpp"
#include "include/physics/vectors.hpp"
#include "include/physics/physobject.hpp"

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
		class rigidbody : component
		{
			private:
				// Save us some RAM using anonymous unions
				union
				{
					// Box2d rigidbody representation
					b2Body *body2D;
					// Bullet rigidbody representation
					btRigidBody *body3D;
				};

				physobject *owner;

				bool ownerSet;

				// See if we should keep calculating it, or not. Useful for optimization
				bool awake;
			public:
				// Constructors
				rigidbody();
				rigidbody(physobject *Owner);

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
				void applyForce(vec2 force, int mode);

				/*	Practically identical to Unity's Rigidbody.AddForce()
				*	@param force The force to apply, based on coordinates
				*	@param mode The mode of the force
				*/
				void applyForce(vec3 force, int mode);

				// Velocity

				// Gets the velocity in the form of a vec2
				vec2 getVelocity2();
				
				// Gets the velocity in the form of a vec3
				vec3 getVelocity3();

				/*	Sets the velocity
				*	@param velocity The new velocity
				*/
				void setVelocity(vec3 velocity);

				/*	Sets the velocity
				*	@param velocity The new velocity
				*/
				void setVelocity(vec2 velocity);

				// Copied from engine::physobject

				// Transform stuff

				/*	Set the position
				*	@param x X position
				*	@param y Y position
				*/
				void setPos(double x, double y);
				/*	Set the position
				*	@param x X position
				*	@param y Y position
				*	@param z Z position
				*/
				void setPos(double x, double y, double z);
				/*	Set the position
				*	@param pos The position
				*/
				void setPos(vec2 pos);
				/*	Set the position
				*	@param pos The position
				*/
				void setPos(vec3 pos);

				/* Set the rotation
				*	@param x Pitch
				*	@param y Yaw
				*/
				void setRot(double x, double y);
				/* Set the rotation
				*	@param x Pitch
				*	@param y Yaw
				*	@param z Roll
				*/
				void setRot(double x, double y, double z);
				/*	Set the rotation
				*	@param pos The rotation
				*/
				void setRot(vec2 rot);
				/*	Set the rotation
				*	@param pos The rotation
				*/
				void setRot(vec3 rot);

				/* Set the scale
				*	@param x X scale
				*	@param y Y scale
				*/
				void setScale(double x, double y);
				/* Set the scale
				*	@param x X scale
				*	@param y Y scale
				*	@param z Z scale
				*/
				void setScale(double x, double y, double z);
				/*	Set the scale
				*	@param scale The scale
				*/
				void setScale(vec2 scale);
				/*	Set the scale
				*	@param pos The scale
				*/
				void setScale(vec3 scale);

				// Advanced physics stuff
				
				/*	Gets the owner, -1 if not set
				*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
				*/
				physobject *getOwner();
		};
	}
}

#endif