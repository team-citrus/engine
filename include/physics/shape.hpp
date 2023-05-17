/*
*   name: include/physics/shape.hpp
*   origin: Citrus Engine
*   purpose: Provides the shape class, used outside of physics too but mainly physics so yeah
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PHYSICS_SHAPES_HPP__
#define CITRUS_ENGINE_PHYSICS_SHAPES_HPP__

#include "../core/mem.hpp"
#include "../core/vector.hpp"
#include "../core/mesh.hpp"
#include "../physics/vectors.hpp"

namespace engine
{
	namespace physics
	{
		class Shape // TODO: Construct as like default shapes
		{
			Vector<Vec2> points;

			public:
			Shape()
			{
				points = Vector<Vec2>(0);
			}

			Shape(Vector<Vec2> &oPoints)
			{
				points = Vector<Vec2>(oPoints.getCount());
				for(size_t i = 0; i < oPoints.getCount(); i++)
				{
					points.push(oPoints[i]);
				}
			}

			OPERATOR Vec2 &operator[](size_t index)
			{
				return points[index];
			}

			OPERATOR size_t pointCount()
			{
				return points.getCount();
			}

			// TODO: more stuff
		};
	}
}

#endif