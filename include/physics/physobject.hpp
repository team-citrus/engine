#ifndef CITRUS_ENGINE_PHYSICS_OBJECTS_HPP__
#define CITRUS_ENGINE_PHYSICS_OBJECTS_HPP__

#include <cstdint>
#include "include/physics/vectors.hpp"

namespace engine
{
	namespace physics
	{
		/*  The underlying class of anything that needs physics
		*   This is directly interfaced by the physics API frequently, and is the primary object for physics code
		*/
		class physobject
		{
			private:

				// Transform is some anonymous unions to save memory and make our lives easier

				// Cordinates, right handed X coordinate
				union
				{
					engine::physics::vec3 coordinates3D;
					engine::physics::vec2 coordinates2D;
				};

				// Rotation, pitch, yaw, and roll form, technically is only used for quaternion conversions in 3d mode
				union
				{
					engine::physics::vec3 rotation3D;
					engine::physics::vec2 rotation2D;
				};

				// Scale, like lens magnification, negative values invert the object on the axis
				union
				{
					engine::physics::vec3 scale3D;
					engine::physics::vec2 scale2D;
				};

				// QUATERNIONS
				engine::physics::vec4 quaternion;

				/*  TODO: Add engine::physics::rigidbody, engine::physics::collider, and engine::object
				*   bool usesRigidbody;
				*
				*   engine::physics::collider *colliders;
				*   engine::physics::rigidbody rigidbody;
				*
				*	Since the pointers for simulations are tagged whenever they are passed to internal functions
				*	We can do things like this with no consequences
				*
				*	union
				*	{
				*   	engine::object *owner;
				*		engine::physics::simulation *sOwner;
				*		uintptr_t ptr;
				*	};
				*	bool ownerSet;
				*/

			public:
				// Constructors
				physobject();
				physobject(vec2 pos);
				physobject(vec2 pos, vec2 rot);
				physobject(vec2 pos, vec2 rot, vec2 scale);
				physobject(vec3 pos);
				physobject(vec3 pos, vec3 rot);
				physobject(vec3 pos, vec3 rot, vec3 scale);

				// Locks
				bool lockPosX, lockPosY, lockPosZ;
				bool lockRotX, lockRotY, lockRotZ;

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
				void setScale(vec3 rot);

				// Advanced physics stuff

				/*	Sets the owner of the physobject.
				*	Assumed to be called when being initialized doubleo the scene.
				*	Locks so it can't be called twice.
				*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
				*	@param owner Pointer to the owner, assumed to be either an object, or a simulation for internal use.
				*/
				void setOwner(void *owner);

				/*	Overrides the owner of the physobject.
				*	Unlocks the owner of the physobject.
				*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
				*	@param owner Pointer to the owner, assumed to be either an object, or a simulation for internal use.
				*/
				void overrideOwner(void *owner);
				
				/*	Gets the owner, tagged if physics simulation
				*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
				*/
				void *getOwner();
		};
	};
};

#endif