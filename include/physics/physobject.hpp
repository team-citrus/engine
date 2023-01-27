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
#include "core/extensions.hpp"
#include "core/component.hpp"

namespace engine
{
	namespace physics
	{
		// The component that enables 2D physics in objects
		class physobject2D : component
		{
			private:
				// Cordinates, right handed X coordinate
				vec2 position;
 
				vec2 rotation;

				// Scale, like lens magnification, negative values invert the object on the axis
				vec2 scale;

				rigidbody2D &rb;

				Vector<collider2D> colliders;

				bool usesRigidbody;

			public:
				// Constructors
				physobject2D()
				{
					position.x = 0;
					position.y = 0;
					rotation.x = 0;
					rotation.y = 0;
					scale.x = 1;
					scale.y = 1;
				}
				physobject2D(vec2 pos)
				{
					position = pos;
					rotation.x = 0;
					rotation.y = 0;
					scale.x = 1;
					scale.y = 1;
				}
				physobject2D(vec2 pos, vec2 rot)
				{
					position = pos;
					rotation = rot;
					scale.x = 1;
					scale.y = 1;
				}
				physobject2D(vec2 pos, vec2 rot, vec2 s)
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
					setPos(vec2(x, y));
				}

				/*	Set the position
				*	@param pos The position
				*/
				OPERATOR void setPos(vec2 pos)
				{
					position = pos;
				}

				/* Set the rotation
				*	@param x Pitch
				*	@param y Yaw
				*/
				OPERATOR void setRot(double x, double y)
				{
					setRot(vec2(x, y));
				}

				/*	Set the rotation
				*	@param pos The rotation
				*/
				OPERATOR void setRot(vec2 rot)
				{
					rotation = rot;
				}

				/* Set the scale
				*	@param x X scale
				*	@param y Y scale
				*/
				OPERATOR void setScale(double x, double y)
				{
					setScale(vec2(x, y));
				}
				
				/*	Set the scale
				*	@param s The scale
				*/
				OPERATOR void setScale(vec2 s)
				{
					scale = s;
				}
				
				// Adding stuff

				/*	Adds a rigidbody to the physobject
				*	@return A reference to the rigidbody
				*/
				OPERATOR rigidbody2D &addRigidbody()
				{
					if(!usesRigidbody)
					{
						usesRigidbody = true;
						rb = getObject().addComponent<rigidbody2D>();
						return (rb = rigidbody3D(*this));
					}
					else
						return rb;
				}

				// Get the position
				OPERATOR vec2 getPos()
				{
					return position;
				}

				// Get the rotation
				OPERATOR vec2 getRot()
				{
					return rotation;
				}

				// Get the scale
				OPERATOR vec2 getScale()
				{
					return scale;
				}

				// Get a reference to the rigidbody, if it's avalible
				OPERATOR rigidbody2D &getRigidbody()
				{
					if(usesRigidbody)
						return rb;
				}

				friend class rigidbody;
		};

		// The component that enables 3D physics in objects
		class physobject3D : component
		{
			private:

				// Transform is some anonymous unions to save memory and make our lives easier

				// Cordinates, right handed X coordinate
				vec3 position;

				// Rotation, euler angle form, technically is only used for quaternion conversions
				vec3 rotation;

				// Scale, like lens magnification, negative values invert the object on the axis
				vec3 scale;

				// QUATERNIONS
				quaternion Quaternion;

				rigidbody3D &rigidbody;

				Vector<collider3D> colliders;

				bool usesRigidbody;

			public:
				// Constructors
				physobject3D()
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
				physobject3D(vec3 pos)
				{
					position = pos;
					rotation.x = 0;
					rotation.y = 0;
					rotation.z = 0;
					scale.x = 0; 
					scale.y = 0;
					scale.z = 0;
				}
				physobject3D(vec3 pos, vec3 rot)
				{
					position = pos;
					rotation = rot;
					scale.x = 0; 
					scale.y = 0;
					scale.z = 0;
				}
				physobject3D(vec3 pos, vec3 rot, vec3 S)
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
					setPos(vec3(x, y, z));
				}

				/*	Set the position
				*	@param pos The position
				*/
				OPERATOR void setPos(vec3 pos)
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
					setRot(vec3(x, y, z));
				}

				/*	Set the rotation
				*	@param pos The rotation
				*/
				OPERATOR void setRot(vec3 rot)
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
					setScale(vec3(x, y, z));
				}

				/*	Set the scale
				*	@param pos The scale
				*/
				OPERATOR void setScale(vec3 S)
				{
					scale = S;
				}
				
				// Adding stuff

				/*	Adds a rigidbody to the physobject
				*	@return A reference to the rigidbody
				*/
				OPERATOR rigidbody3D &addRigidbody()
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
				OPERATOR vec3 getPos()
				{
					return position;
				}

				// Get the rotation
				OPERATOR vec3 getRot()
				{
					return rotation;
				}

				// Get the scale
				OPERATOR vec3 getScale()
				{
					return scale;
				}

				// Get a reference to the rigidbody, if it's avalible
				OPERATOR rigidbody3D &getRigidbody()
				{
					if(usesRigidbody)
						return rb;
				}

				friend class rigidbody;
		};
	};
};

#endif