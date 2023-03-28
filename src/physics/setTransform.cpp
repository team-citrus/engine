/*
*   name: src/physics/setTransform.cpp
*   origin: Citrus Engine
*   purpose: Provides for modifing the transforms of physics objects
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <cstdlib>
#include "core/extensions.h"
#include "physics/vectors.hpp"
#include "physics/physobject.hpp"
#include "physics/rigidbody.hpp"

using namespace engine;
using namespace physics;

OPERATOR void rigidbody::setPos(double x, double y)
{
    if(ownerSet)
        owner->setPos(x, y);

    return;
}

OPERATOR void rigidbody::setPos(double x, double y, double z)
{
    if(ownerSet)
        owner->setPos(x, y, z);
    return;
}

void rigidbody::setPos(Vec2 pos)
{
    if(ownerSet)
        owner->setPos(pos);
    return;
}

void rigidbody::setPos(Vec3 pos)
{
    if(ownerSet)
        owner->setPos(pos);
    return;
}

OPERATOR void physobject::setPos(double x, double y)
{
    setPos(Vec2(x, y));
    return;
}

OPERATOR void physobject::setPos(double x, double y, double z)
{
    setPos(Vec3(x, y, z));
    return;
}

void physobject::setPos(Vec2 pos)
{
    coordinates2D = pos;
}

void physobject::setPos(Vec3 pos)
{
    coordinates3D = pos;
}

OPERATOR void rigidbody::setRot(double x, double y)
{
    if(ownerSet)
        owner->setRot(x, y);
    return;
}

OPERATOR void rigidbody::setRot(double x, double y, double z)
{
    if(ownerSet)
        owner->setRot(x, y, z);
    return;
}

void rigidbody::setRot(Vec2 rot)
{
    if(ownerSet)
        owner->setRot(rot);
    return;
}

void rigidbody::setRot(Vec3 rot)
{
    if(ownerSet)
        owner->setRot(rot);
    return;
}

OPERATOR void physobject::setRot(double x, double y)
{
    setRot(Vec2(x, y));
    return;
}

OPERATOR void physobject::setRot(double x, double y, double z)
{
    setRot(Vec3(x, y, z));
    return;
}

void physobject::setRot(Vec2 rot)
{
    rotation2D = rot;
}

void physobject::setRot(Vec3 rot)
{
    rotation3D = rot;
}

OPERATOR void rigidbody::setScale(double x, double y)
{
    if(ownerSet)
        owner->setScale(x, y);
    return;
}

OPERATOR void rigidbody::setScale(double x, double y, double z)
{
    if(ownerSet)
        owner->setScale(x, y, z);
    return;
}

void rigidbody::setScale(Vec2 scale)
{
    if(ownerSet)
        owner->setScale(scale);
    return;
}

void rigidbody::setScale(Vec3 scale)
{
    if(ownerSet)
        owner->setScale(scale);
    return;
}

OPERATOR void physobject::setScale(double x, double y)
{
    setScale(Vec2(x, y));
    return;
}

OPERATOR void physobject::setScale(double x, double y, double z)
{
    setScale(Vec3(x, y, z));
    return;
}

void physobject::setScale(Vec2 scale)
{
    coordinates2D = scale;
}

void physobject::setScale(Vec3 scale)
{
    coordinates3D = scale;
}