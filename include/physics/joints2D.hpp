/*
*   name: include/physics/joints2D.hpp
*   origin: Citrus Engine
*   purpose: Provide joints
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_RIGIDBODIES_HPP__
#define CITRUS_ENGINE_RIGIDBODIES_HPP__

#include "../core/component.hpp"
#include "../physics/rigidbody.hpp"

namespace engine
{
	namespace internals { namespace physics { struct Joint2DTuple { Object *owner; engine::physics::Joint2D *Component; }; } }
	namespace physics
	{
		enum JointType2D
		{ 
			DistanceJoint = 0,
			FrictionJoint,
			GearJoint,
			MotorJoint,
			PulleyJoint,
			WeldJoint,
			WheelJoint,
		};

		class Joint2D : Component
		{
			internals::physics::Joint2DTuple tuple;
			JointType2D type;
			Rigidbody2D *a;
			Rigidbody2D *b;
			bool collide;
			public:
			void init();

			void setType();
			JointType2D getType();

			Rigidbody2D *getBodyA();
			Rigidbody2D *getBodyB();
			const Rigidbody2D *getBodyA() const;
			const Rigidbody2D *getBodyB() const;
			void setBodyA(Rigidbody2D &bodyA);
			void setBodyB(Rigidbody2D &bodyB);

			Vec2 getReactionForce();
			float getReactionTorque();

			void setCollideConnected(bool b);
			bool getCollideConnected() const;

			bool isEnabled() const;
		};

		class DistanceJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;
			float length;
			float minLength;
			float maxLength;
			float stiffness;
			float damping;
			public:
			void setAnchorA(Vec2 anchor);
			void setAnchorB(Vec2 anchor);
			Vec2 getAnchorA() const;
			Vec2 getAnchorb() const;

			void setLength(float f);
			float getLength() const;

			void setMinLength(float f);
			float getMinLength() const;
			void setMaxLength(float f);
			float getMaxLength() const;

			void setStiffness(float f);
			float getStiffness() const;

			void setDamping(float f);
			float getDamping() const;
		};
	}
}

#endif	