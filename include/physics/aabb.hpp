/*
*   name: include/physics/aabb.hpp
*   origin: Citrus Engine
*   purpose: Provide a class for 2D AABBs
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PHYSICS_AABB
#define CITRUS_ENGINE_PHYSICS_AABB

#include "../physics/vectors.hpp"

namespace engine
{
	namespace physics
	{
		class AABB2D
		{
			void *body2D;
			Vec2 center;
			Vec2 extents;
			public:
			Vec2 getCenter() const;
			void setCenter(Vec2 c);

			Vec2 getExtents() const;
			void setExtents(Vec2 e);

			float getPerimeter() const;

			void combine(AABB2D &a);
			
			bool has(AABB2D a);
		}
	}
}

#endif