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
			Vector<size_t> indexes;

			public:
			Shape()
			{
				points = Vector<Vec2>(0);
				indexes = Vector<size_t>(0);
			}

			Shape(Vector<Vec2> &oPoints)
			{
				points = Vector<Vec2>(0);
				indexes = Vector<size_t>(oPoints.getCount());
				for(size_t i = 0; i < oPoints.getCount(); i++)
				{
					if(points.search(oPoints[i]) != -1)
					{
						indexes.push(points.search(oPoints[i]));
					}
					else
					{
						indexes.push(points.getCount());
						points.push(oPoints[i]);
					}
				}
			}	

			// TODO: more stuff
		};
	}
}

#endif