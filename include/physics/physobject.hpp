/*
*   name: include/physics/physobject.hpp
*   origin: Citrus Engine
*   purpose: Provides the engine::physics::physobject class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PHYSICS_OBJECTS_HPP__
#define CITRUS_ENGINE_PHYSICS_OBJECTS_HPP__

#include <cstdint>
#include "physics/rigidbody.hpp"
#include "physics/vectors.hpp"
#include "physics/collider.hpp"
#include "core/extensions.h"
#include "core/component.hpp"

namespace engine
{
	namespace physics
	{
		// The component that enables 2D physics in objects
		class Physobject2D : Component
		{
			private:
				// Cordinates, right handed X coordinate
				Vec2 position;
 
				Vec2 rotation;

				// Scale, like lens magnification, negative values invert the object on the axis
				Vec2 scale;

				Rigidbody2D &rb;

				Vector<Collider2D> colliders;

				bool usesRigidbody;

			public:
				// Constructors
				Physobject2D()
				{
					position.x = 0;
					position.y = 0;
					rotation.x = 0;
					rotation.y = 0;
					scale.x = 1;
					scale.y = 1;
				}
				Physobject2D(Vec2 pos)
				{
					position = pos;
					rotation.x = 0;
					rotation.y = 0;
					scale.x = 1;
					scale.y = 1;
				}
				Physobject2D(Vec2 pos, Vec2 rot)
				{
					position = pos;
					rotation = rot;
					scale.x = 1;
					scale.y = 1;
				}
				Physobject2D(Vec2 pos, Vec2 rot, Vec2 s)
				{
					position = pos;
					rotation = rot
					scale = s;
				}

				// Locks
				bool lockPosX, lockPosY;
				bool lockRotX, lockRotY;

				// Transform stuff

				/*	Set the position
				*	@param x X position
				*	@param y Y position
				*/
				OPERATOR void setPos(double x, double y)
				{
					setPos(Vec2(x, y));
				}

				/*	Set the position
				*	@param pos The position
				*/
				OPERATOR void setPos(Vec2 pos)
				{
					position = pos;
				}

				/* Set the rotation
				*	@param x Pitch
				*	@param y Yaw
				*/
				OPERATOR void setRot(double x, double y)
				{
					setRot(Vec2(x, y));
				}

				/*	Set the rotation
				*	@param pos The rotation
				*/
				OPERATOR void setRot(Vec2 rot)
				{
					rotation = rot;
				}

				/* Set the scale
				*	@param x X scale
				*	@param y Y scale
				*/
				OPERATOR void setScale(double x, double y)
				{
					setScale(Vec2(x, y));
				}
				
				/*	Set the scale
				*	@param s The scale
				*/
				OPERATOR void setScale(Vec2 s)
				{
					scale = s;
				}
				
				// Adding stuff

				/*	Adds a rigidbody to the physobject
				*	@return A reference to the rigidbody
				*/
				OPERATOR Rigidbody2D &addRigidbody()
				{
					if(!usesRigidbody)
					{
						usesRigidbody = true;
						rb = getObject().addComponent<rigidbody2D>();
						return (rb = Rigidbody3D(*this));
					}
					else
						return rb;
				}

				// Get the position
				OPERATOR Vec2 getPos()
				{
					return position;
				}

				// Get the rotation
				OPERATOR Vec2 getRot()
				{
					return rotation;
				}

				// Get the scale
				OPERATOR Vec2 getScale()
				{
					return scale;
				}

				// Get a reference to the rigidbody, if it's avalible
				OPERATOR Rigidbody2D &getRigidbody()
				{
					if(usesRigidbody)
						return rb;
				}

				friend class Rigidbody2D;
		};

		// The Component that enables 3D physics in objects
		class Physobject3D : Component
		{
			private:

				// Transform is some anonymous unions to save memory and make our lives easier

				// Cordinates, right handed X coordinate
				Vec3 position;

				// Rotation, euler angle form, technically is only used for quaternion conversions
				Vec3 rotation;

				// Scale, like lens magnification, negative values invert the object on the axis
				Vec3 scale;

				// QUATERNIONS
				Quaternion quat;

				Rigidbody3D &rigidbody;

				Vector<Collider3D> colliders;

				bool usesRigidbody;

			public:
				// Constructors
				Physobject3D()
				{
					position.x = 0;
					position.y = 0;
					position.z = 0;
					rotation.x = 0;
					rotation.y = 0;
					rotation.z = 0;
					scale.x = 0; 
					scale.y = 0;
					scale.z = 0;
				}
				Physobject3D(Vec3 pos)
				{
					position = pos;
					rotation.x = 0;
					rotation.y = 0;
					rotation.z = 0;
					scale.x = 0; 
					scale.y = 0;
					scale.z = 0;
				}
				Physobject3D(Vec3 pos,Vec3 rot)
				{
					position = pos;
					rotation = rot;
					scale.x = 0; 
					scale.y = 0;
					scale.z = 0;
				}
				Physobject3D(Vec3 pos,Vec3 rot,Vec3 S)
				{
					position = pos;
					rotation = rot;
					scale = S;
				}

				// Locks
				bool lockPosX, lockPosY, lockPosZ;
				bool lockRotX, lockRotY, lockRotZ;

				// Transform stuff

				/*	Set the position
				*	@param x X position
				*	@param y Y position
				*	@param z Z position
				*/
				OPERATOR void setPos(double x, double y, double z)
				{
					setPos(Vec3(x, y, z));
				}

				/*	Set the position
				*	@param pos The position
				*/
				OPERATOR void setPos(Vec3 pos)
				{
					position = pos;
				}

				/* Set the rotation
				*	@param x Pitch
				*	@param y Yaw
				*	@param z Roll
				*/
				OPERATOR void setRot(double x, double y, double z)
				{
					setRot(Vec3(x, y, z));
				}

				/*	Set the rotation
				*	@param pos The rotation
				*/
				OPERATOR void setRot(Vec3 rot)
				{
					rotation = rot;
				}

				/* Set the scale
				*	@param x X scale
				*	@param y Y scale
				*	@param z Z scale
				*/
				OPERATOR void setScale(double x, double y, double z)
				{
					setScale(Vec3(x, y, z));
				}

				/*	Set the scale
				*	@param pos The scale
				*/
				OPERATOR void setScale(Vec3 S)
				{
					scale = S;
				}
				
				// Adding stuff

				/*	Adds a rigidbody to the physobject
				*	@return A reference to the rigidbody
				*/
				OPERATOR Rigidbody3D &addRigidbody()
				{
					if(!usesRigidbody)
					{
						usesRigidbody = true;
						rb = getObject().addComponent<rigidbody3D>();
						return (rb = rigidbody3D(*this));
					}
					else
						return rb;
				}

				// Get the position
				OPERATORVec3 getPos()
				{
					return position;
				}

				// Get the rotation
				OPERATORVec3 getRot()
				{
					return rotation;
				}

				// Get the scale
				OPERATORVec3 getScale()
				{
					return scale;
				}

				// Get a reference to the rigidbody, if it's avalible
				OPERATOR Rigidbody3D &getRigidbody()
				{
					if(usesRigidbody)
						return rb;
				}

				friend class Rigidbody3D;
		};
	};
};

#endif