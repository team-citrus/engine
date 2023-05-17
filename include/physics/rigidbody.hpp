/*
*   name: include/physics/rigidbody.hpp
*   origin: Citrus Engine
*   purpose: Provides the engine::physics::rigidbody class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_RIGIDBODIES_HPP__
#define CITRUS_ENGINE_RIGIDBODIES_HPP__

#include "../core/object.hpp"
#include "../core/transform.hpp"
#include "../core/transform.hpp"
#include "../core/extensions.h"
#include "../physics/vectors.hpp"
#include "../physics/collider.hpp"

#define RB_FORCEMODE_IMPULSE 0
#define RB_FORCEMODE_FORCE 1
#define RB_FORCEMODE_ACCELERATION 2
#define RB_FORCEMODE_VELOCITY 3

#define RB_KINEMATIC 0
#define RB_STATIC 1
#define RB_DYNAMIC 2

#define RB_AWAKE true
#define RB_ASLEEP false

namespace engine
{
	namespace physics
	{
		class Rigidbody2D : Component
		{
			private:
				// Box2d rigidbody representation
				void *body2D;
				friend class Collider2D;

				// stuff

				int type;
				Transform2D &trans; // rigidbodies take control of transform after being init'd
				Vec2 velocity;
				float angularVelocity;
				float linearDamping;
				float angularDamping;
				bool fixedRotation;
				bool bullet;
				bool enabled;
				float gravityScale;
			public:
				// Actually create the rigidbody
				int init();

				Vec2 getCenterOfMass() const;
				Vec2 getCenterOfMassLocal() const;

				void setVelocity(Vec2 vel);
				Vec2 getVelocity() const;

				void setAngularVelocity(float omega);
				float getAngularVelocity() const;

				void applyForce(const Vec2 force, bool wake, int type);
				void applyForce(const Vec2 force, const Vec2 point, bool wake, int type);

				// TODO: relativeForce() and forceAtPoint()

				float getMass() const;
				// TODO: setter for mass

				float getLinearDamping() const;
				void setLinearDamping(float f);

				float getAngularDamping() const;
				void setAngularDamping(float f);

				float getScaleOfGravity() const;
				void setScaleOfGravity(float s);

				void setType(int type);
				int getType() const;

				void setBullet(bool b);
				bool isBullet() const;

				void sleep();
				void wake();
				bool isAwake() const;

				void disable();
				void enable();
				bool isEnabled() const;

				void lockRotation();
				void unlockRotation();
				bool isRotationLocked();
				
				Collider2D &addCollider()
				{
					Collider2D &r = getObject().addComponent<Collider2D>();
					r.rb = this;
					return r;
				} // TODO: shape
		};

		class Rigidbody3D : Component
		{
			private:
				// Bullet rigidbody representation
				void *body3D;
			public:
		};
	}
}

#endif