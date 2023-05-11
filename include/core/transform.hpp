/*
*   name: include/core/transform.hpp
*   origin: Citrus Engine
*   purpose: Provide engine::transform2D, and engine::transform3D
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_TRANSFORM_HPP__
#define CITRUS_ENGINE_TRANSFORM_HPP__

#include "../core/extensions.h"
#include "../core/component.hpp"
#include "../physics/vectors.hpp"

namespace engine
{
	using Float2 = physics::Vec2;
	using Float3 = physics::Vec3;
	using Float4 = physics::Vec4;

	class Transform2D : Component
	{
		public:
			Float2 position;

			float rotation;

			Float2 scale;

			virtual void awake()
			{
				return;
			}
			virtual void start()
			{
				return;
			}
			virtual void update()
			{
				return;
			}
			
			virtual void fixedUpdate()
			{
				return;
			}
			virtual void onTriggerEnter()
			{
				return;
			}
			virtual void onTriggerStay()
			{
				return;
			}
			virtual void onTriggerExit()
			{
				return;
			}
	}

	class Transform3D : Component
	{
		public:
			Float3 position;

			Float3 rotation;

			Float3 scale;

			virtual void awake()
			{
				return;
			}
			virtual void start()
			{
				return;
			}
			virtual void update()
			{
				return;
			}
			
			virtual void fixedUpdate()
			{
				return;
			}
			virtual void onTriggerEnter()
			{
				return;
			}
			virtual void onTriggerStay()
			{
				return;
			}
			virtual void onTriggerExit()
			{
				return;
			}
	}
};

#endif