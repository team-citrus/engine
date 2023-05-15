/*
*   name: include/physics/collider.hpp
*   origin: Citrus Engine
*   purpose: Provides collider classes
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PHYSICS_COLLIDIERS_HPP__
#define CITRUS_ENGINE_PHYSICS_COLLIDIERS_HPP__

#include "../core/component.hpp"
#include "../core/object.hpp"
#include "../physics/rigidbody.hpp"
#include "../physics/shape.hpp"

namespace engine
{
	namespace internals
	{
		namespace physics
		{
			struct Collider2DTouple
			{
				Object *o;
				engine::physics::Collider2D *c;
			};
		}
	}
	namespace physics
	{
		// TODO: engine::"physics::"shape

		class Collider2D : Component
		{
			friend class Rigidbody2D;
			void *fixture; // Pointer to the Box2D version
			Rigidbody2D *rb;
			engine::physics::Shape shape;

			internals::physics::Collider2DTouple t;
			bool isTrigger;
			float friction;
			float resitituion;
			float restitutionThreshold;
			float density;
			// TODO: filter

			public:
			void init();
			void init(Shape s);

			void setTriggerStatus(bool t);
			bool getTriggerStatus() const;

			void setDensity(float d);
			float getDensity() const;

			void setFriction(float f);
			float getFriction() const;

			void setRestitution(float r);
			float getRestitution() const;

			void setRestitutionThreshold(float t);
			float getRestitutionThreshold();
		};
	}
}

#endif