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
			PrismaticJoint,
			RevoluteJoint,
		};

		class Joint2D : public Component
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

			virtual Vec2 getReactionForce(float f) const = 0;
			virtual float getReactionTorque(float f) const = 0;

			void setCollideConnected(bool b);
			bool getCollideConnected() const;

			bool isEnabled() const;
		};

		class DistanceJoint2D : public Joint2D
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

		class FrictionJoint2D : public Joint2D
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

		class GearJoint2D : public Joint2D
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

			Vec2 getReactionForce(float f) const override;
			float getReactionTorque(float f) const override;

			void setRatio(float r);
			float getRatio() const;
		};

		class MotorJoint2D : public Joint2D
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

			Vec2 getReactionForce(float f) const override;
			float getReactionTorque(float f) const override;

			void setMaxForce(float f);
			float getMaxForce() const;

			void setMaxTorque(float f);
			float getMaxTorque() const;

			void setCorrectionFactor(float f);
			float getCorrectionFactor() const;
		};

		class PrismaticJoint2D : public Joint2D
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

			Vec2 getReactionForce(float f) const override;
			float getReactionTorque(float f) const override;

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

		class PulleyJoint2D : public Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			Vec2 groundAnchorA;
			Vec2 groundAnchorB;

			float lengthA;
			float lengthB;

			float ratio;
			public:
			void init() override;

			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 b) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			Vec2 getReactionForce(float f) const override; 
			float getReactionTorque(float f) const override;

			Vec2 getGroundAnchorA() const;
			Vec2 getGroundAnchorB() const;
	f		void setGroundAnchorA(Vec2 a);
			void setGroundAnchorB(Vec2 b);

			float getLengthA() const;
			float getLengthB() const;
			void setLengthA(float a);
			void setLengthB(float b);

			float getRatio() const;
			void setRatio(float r);
		};
		
		class WeldJoint2D : public Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			float referenceAngle;
			float stiffness;
			float damping;
			public:
			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 b) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			Vec2 getReactionForce(float f) const override;
			float getReactionTorque(float f) const override;

			float getRefernceAngle() const;

			void setStiffness(float s);
			float gotStiffness() const;

			void setDamping(float d);
			float getDamping() const;
		};

		class WheelJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;
			
			Vec2 axis;

			bool enableLimit;
			float upperTranslation;
			float lowerTranslation;

			bool enableMotor;
			float maxMotorTorque;
			float motorSpeed;

			float stiffness;
			float damping;
			public:
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;
			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 b) override;

			Vec2 getAxis() const;
			void setAxis(Vec2 a);

			Vec2 getReactionForce(float f) const override;
			float getReactionTorque(float f) const override;

			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;
			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 a) override;

			float getJointTranslation() const;
			float getJointLinearSpeed() const;
			float getJointAngle() const;
			float getJointAngularSpeed() const;

			bool isLimitEnabled() const;
			void enableLimit();
			void disableLimit();

			float getLowerLimit() const;
			float getUpperLimit() const;
			void setLimits(float upper, float lower);

			bool isMotorEnabled() const;
			void disableMotor();
			void enableMotor();

			float getMotorSpeed() const;
			void setMotorSpeed(float s);

			float getMaxMotorTorque() const;
			void setMaxMotorTorque(float t);

			float getStiffness() const;
			void setStiffness(float s);

			float getDamping() const;
			void setDamping(float d);
		};

		class RevoluteJoint2D : Joint2D
		{
			Vec2 anchorA;
			Vec2 anchorB;

			float referenceAngle;
			bool enableLimit;

			float lowerAngle;
			float upperAngle;

			bool enableMotor;
			float motorSpeed;
			float maxMotorTorque;
			public:
			void setAnchorA(Vec2 a) override;
			void setAnchorB(Vec2 a) override;
			Vec2 getAnchorA() const override;
			Vec2 getAnchorB() const override;

			float getReferenceAngle() const;
			void setReferenceAngle(float a);
			
			float getJointAngle() const;
			float getJointSpeed() const;

			bool isLimitEnabled() const;
			void enableLimit();
			void disableLimit();

			float getLowerLimit() const;
			float getUpperLimit() const;
			void setLimits(float upper, float lower);

			bool isMotorEnabled() const;
			void enableMotor();
			void disableMotor();

			float getMotorSpeed() const;
			void setMotorSpeed(float s);

			float getMaxMotorTorque() const;
			void setMaxMotorTorque(float t);

			Vec2 getReactionForce(float f) const override;
			float getReactionTorque(float f) const override;

			float getMotorTorque() const;
		};
	}
}

#endif