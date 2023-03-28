/*
*   name: include/physics/collider.hpp
*   origin: Citrus Engine
*   purpose: Provides collider classes
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COLLIDER_HPP__
#define CITRUS_ENGINE_COLLIDER_HPP__

#include <cstdint>
#include "physics/physobject.hpp"
#include "physics/vectors.hpp"
#include "core/extensions.h"
#include "core/component.hpp"

// 3D Collider types

#define COLLIDER_TYPE_CUBE 0
#define COLLIDER_TYPE_CYLINDER 1
#define COLLIDER_TYPE_SPHERE 2
#define COLLIDER_TYPE_PLANE 3
#define COLLIDER_TYPE_QUAD 4

// 2D Collider types

#define COLLIDER_TYPE_SQUARE 0x80000000
#define COLLIDER_TYPE_CIRCLE 0x80000001
#define COLLIDER_TYPE_TRIANGLE 0x80000002
#define COLLIDER_TYPE_PENTAGON 0x80000003
#define COLLIDER_TYPE_HEXAGON 0x80000004

// Custom collider

#define COLLIDER_TYPE_CUSTOM -1

namespace engine
{
	namespace physics
	{
		class Collider2D : Component
		{
			private:
				// Transform is some anonymous unions to save memory and make our lives easier

				// Cordinates, right handed X coordinate
				Vec2 coordinates;

				Vec2 rotation;

				// Scale, like lens magnification, negative values invert the object on the axis
				Vec2 scale;

				Physobject2D *owner;

				/*  TODO: add engine::shape;
				*   shape bshape
				*/
			public:
				// Constructors
				Collider();
				Collider(int type);
				Collider(bool trigger);
				Collider(int type, bool trigger);
				/*  TODO: add engine::shape
				*   collider(shape base);
				*   collider(shape base, bool trigger);
				*/

			   // Transform stuff

				/*	Set the position, relative to the owner
				*	@param x X position
				*	@param y Y position
				*/
				void setPos(double x, double y);
				
				/*	Set the position, relative to the owner
				*	@param pos The position
				*/
				void setPos(Vec2 pos);

				/* Set the rotation, relative to the owner
				*	@param x Pitch
				*	@param y Yaw
				*/
				void setRot(double x, double y);
				
				/*	Set the rotation, relative to the owner
				*	@param pos The rotation
				*/
				void setRot(Vec2 rot);

				/*  Set the scale, relative to the owner
				*	@param x X scale
				*	@param y Y scale
				*/
				void setScale(double x, double y);
				
				/*	Set the scale, relative to the owner
				*	@param scale The scale
				*/
				void setScale(Vec2 scale);

				// Advanced physics stuff
				
				//	Gets the owner
				Physobject2D &getPhysobject();
		};

		class Collider3D : Component
		{
			private:
				// Transform is some anonymous unions to save memory and make our lives easier

				// Cordinates, right handed X coordinate
				Vec3 coordinates;

				// Rotation, pitch, yaw, and roll form, technically is only used for quaternion conversions in 3d mode
				Vec3 rotation;

				// Scale, like lens magnification, negative values invert the object on the axis
				Vec3 scale;

				// QUATERNIONS
				Quaternion quat;

				Physobject3D *owner;

				/*  TODO: add engine::mesh
				*	mesh bmesh;
				*/
			public:
				// Constructors
				collider3D();
				collider3D(int type);
				collider3D(bool trigger);
				collider3D(int type, bool trigger);
				/*  TODO: add engine::mesh
				*   collider(mesh base);
				*   collider(mesh base, bool trigger);
				*/

				// Transform stuff

				
				/*	Set the position, relative to the owner
				*	@param x X position
				*	@param y Y position
				*	@param z Z position
				*/
				void setPos(double x, double y, double z);
				
				/*	Set the position, relative to the owner
				*	@param pos The position
				*/
				void setPos(Vec3 pos);

				/* Set the rotation, relative to the owner 
				*	@param x Pitch
				*	@param y Yaw
				*	@param z Roll
				*/
				void setRot(double x, double y, double z);
				
				/*	Set the rotation, relative to the owner
				*	@param pos The rotation
				*/
				void setRot(Vec3 rot);

				/* Set the scale, relative to the owner
				*	@param x X scale
				*	@param y Y scale
				*	@param z Z scale
				*/
				void setScale(double x, double y, double z);
				
				/*	Set the scale, relative to the owner
				*	@param pos The scale
				*/
				void setScale(Vec3 scale);

				// Advanced physics stuff
				
				//	Gets the owner
				Physobject3D &getPhysobject();
		};
	};
};

#endif