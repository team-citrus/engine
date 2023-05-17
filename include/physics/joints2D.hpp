/*
*   name: include/physics/joints2D.hpp
*   origin: Citrus Engine
*   purpose: Provide joints
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_JOINTS2D_HPP__
#define CITRUS_ENGINE_JOINTS2D_HPP__

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
			void *body2D;

			Rigidbody2D *a;
			Rigidbody2D *b;

			bool collide;

			Vec2 anchorA;
			Vec2 anchorB;
			public:
			virtual void init();

			void setType();
			JointType2D getType();

			Rigidbody2D *getBodyA();
			Rigidbody2D *getBodyB();
			const Rigidbody2D *getBodyA() const;
			const Rigidbody2D *getBodyB() const;
			void setBodyA(Rigidbody2D &bodyA);
			void setBodyB(Rigidbody2D &bodyB);

			virtual Vec2 getAnchorA() const = 0;
			virtual Vec2 getAnchorB() const = 0;
			virtual void setAnchorA(Vec2 a) = 0;
			virtual void setAnchorB(Vec2 b) = 0;

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
			void init() override;

			void setAnchorA(Vec2 anchor) override;
			void setAnchorB(Vec2 anchor) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

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

		class FrictionJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			float maxFriction;
			float maxTorque;
			public:
			void init() override;

			void setAnchorA(Vec2 anchor) override;
			void setAnchorB(Vec2 anchor) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			void setMaxForce(float f);
			float getMaxForce() const;

			void setMaxTorque(float f);
			float getMaxTorque() const;
		};

		class GearJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			float ratio;
			Joint2D *jointA;
			Joint2D *jointB;
			public:
			void init() override;

			void setAnchorA(Vec2 anchor) override;
			void setAnchorB(Vec2 anchor) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			Vec2 getReactionForce() const;
			float getReactionTorque() const;

			void setRatio(float r);
			float getRatio() const;
		};

		class MotorJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			float maxForce;
			float maxTorque;
			float correctionFactor;
			float angularOffset;
			Vec2 linearOffset;
			public:
			void init() override;

			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 a) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			void setLinearOffset(Vec2 v);
			Vec2 getLinearOffset() const;

			void setAngularOffset(float o);
			float getAngularOffset() const;

			Vec2 getReactionForce() const;
			float getReactionTorque() const;

			void setMaxForce(float f);
			float getMaxForce() const;

			void setMaxTorque(float f);
			float getMaxTorque() const;

			void setCorrectionFactor(float f);
			float getCorrectionFactor() const;
		};

		class PrismaticJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			float referenceAngle;
			bool enableLimit;
			float lowerTranslation;
			float upperTranslation;
			bool enableMotor;
			float maxMotorForce;
			float motorSpeed;
			public:
			void init() override;

			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 a) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			Vec2 getReactionForce() const;
			float getReactionTorque() const;

			Vec2 getAxisA() const;

			void setReferenceAngle(float a);
			float getReferenceAngle() const;

			void setJointLowerTranslationLimit(float l);
			void setJointUpperTranslationLimit(float u);

			float getJointTranslation() const;
			
			float getJointSpeed() const;
			
			bool isLimitEnabled() const;
			void enableLimit();
			void disableLimit();

			float getLowerLimit() const;
			float getUpperLimit() const;
			void setLimits(float upper, float lower);

			bool isMotorEnabled() const;
			void enableMotor() const;
			void disableMotor() const;

			void setMotorSpeed(float s);
			float getMotorSpeed() const;

			float getMaxMotorForce() const;
			void setMaxMotorForce(float f);
			float getMotorForce(float n) const;
		};
	}
}

#endif