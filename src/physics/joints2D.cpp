/*
*   name: src/physics/joints2D.cpp
*   origin: Citrus Engine
*   purpose: Provide joints
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <box2d/box2d.h>
#include "physics/joints2D.hpp"
#include "physics/rigidbody.hpp"
#include "core/errno.hpp"

void engine::physics::Joint2D::init()
{
    switch(type)
    {
        case engine::physics::JointType2D::DistanceJoint:
        ((engine::physics::DistanceJoint2D*)this)->engine::physics::DistanceJoint2D::init();
        return;

        case engine::physics::JointType2D::FrictionJoint:
        ((engine::physics::FrictionJoint2D*)this)->engine::physics::FrictionJoint2D::init();
        return;

        case engine::physics::JointType2D::GearJoint:
        ((engine::physics::GearJoint2D*)this)->engine::physics::GearJoint2D::init();
        return;

        case engine::physics::JointType2D::MotorJoint:
        ((engine::physics::MotorJoint2D*)this)->engine::physics::MotorJoint2D::init();
        return;

        case engine::physics::JointType2D::PulleyJoint:
        ((engine::physics::PulleyJoint2D*)this)->engine::physics::PulleyJoint2D::init();
        return;

        case engine::physics::JointType2D::WheelJoint:
        ((engine::physics::WheelJoint2D*)this)->engine::physics::WheelJoint2D::init();
        return;

        case engine::physics::JointType2D::WeldJoint:
        ((engine::physics::WeldJoint2D*)this)->engine::physics::WeldJoint2D::init();
        return;

        case engine::physics::JointType2D::PrismaticJoint:
        ((engine::physics::PrismaticJoint2D*)this)->engine::physics::PrismaticJoint2D::init();
        return;

        case engine::physics::JointType2D::RevoluteJoint:
        ((engine::physics::RevoluteJoint2D*)this)->engine::physics::RevoluteJoint2D::init();
        return;

        default:
        errorcode() = ENGINE_INVALID_ARG;
        return;
    }
}

void engine::physics::DistanceJoint2D::init()
{
    b2DistanceJointDef def;
    def.type = b2JointType::e_distanceJoint;

    def.bodyA = (b2Body*)(a->body2D);
    def.bodyB = (b2Body*)(b->body2D);

    def.collideConnected = collide;

    def.localAnchorA = *(b2Vec2*)&anchorA;
    def.localAnchorB = *(b2Vec2*)&anchorB;

    def.maxLength = maxLength;
    def.minLength = minLength;
    def.length = length;

    def.stiffness = stiffness;
    def.damping = damping;

    // TODO: FUCKING def.Initalize()
}

void engine::physics::FrictionJoint2D::init()
{
    b2FrictionJointDef def;
    def.type = b2JointType::e_frictionJoint;

    def.bodyA = (b2Body*)(a->body2D);
    def.bodyB = (b2Body*)(b->body2D);

    def.localAnchorA = *(b2Vec2*)&anchorA;
    def.localAnchorB = *(b2Vec2*)&anchorB;

    def.maxForce = maxForce;
    def.maxTorque = maxTorque;

    // TODO: FUCKING def.Initalize()
}

void engine::physics::GearJoint2D::init()
{
    b2GearJointDef def;
    def.type = b2JointType::e_gearJoint;

    def.joint1 = (b2Joint*)jointA->body2D;
    def.joint2 = (b2Joint*)jointB->body2D;
    

    def.bodyA = (b2Body*)a->body2D;
    def.bodyB = (b2Body*)b->body2D;

    def.collideConnected = collide;
    
    def.ratio = ratio;

    def.userData.pointer = (uintptr_t)&tuple;
}

void engine::physics::MotorJoint2D::init()
{
    b2GearJointDef def;
    def.type = b2JointType::e_motorJoint;

    def.joint1 = (b2Joint*)jointA->body2D;
    def.joint2 = (b2Joint*)jointB->body2D;

    def.bodyA = (b2Body*)a->body2D;
    def.bodyB = (b2Body*)b->body2D;

    def.collideConnected = collide;

    def.ratio = ratio;

    def.userData.pointer = (uintptr_t)&tuple;
}

void engine::physics::PrismaticJoint2D::init()
{
    b2PrismaticJointDef def;
    def.type = b2JointType::e_prismaticJoint;

    def.bodyA = (b2Body*)a->body2D;
    def.bodyB = (b2Body*)b->body2D;

    def.collideConnected = collide;

    def.enableLimit = limitEnabled;
    def.enableMotor = motorEnabled;

    def.localAnchorA = b2Vec2(anchorA.x, anchorB.y);
    def.localAnchorB = b2Vec2(anchorB.x, anchorB.y);
    
    def.localAxisA = b2Vec2(axis.x, axis.y);

    def.lowerTranslation = lowerTranslation;
    def.upperTranslation = upperTranslation;

    def.maxMotorForce = maxMotorForce;
    def.motorSpeed = motorSpeed;

    def.referenceAngle = referenceAngle;

    def.userData.pointer = (uintptr_t)&tuple;
}