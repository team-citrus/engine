/*
*   name: src/physics/setTransform.cpp
*   origin: Citrus Engine
*   purpose: Provides for modifing the transforms of physics objects
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <cstdlib>
#include "core/extensions.hpp"
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

void rigidbody::setPos(vec2 pos)
{
    if(ownerSet)
        owner->setPos(pos);
    return;
}

void rigidbody::setPos(vec3 pos)
{
    if(ownerSet)
        owner->setPos(pos);
    return;
}

OPERATOR void physobject::setPos(double x, double y)
{
    setPos(vec2(x, y));
    return;
}

OPERATOR void physobject::setPos(double x, double y, double z)
{
    setPos(vec3(x, y, z));
    return;
}

void physobject::setPos(vec2 pos)
{
    coordinates2D = pos;
}

void physobject::setPos(vec3 pos)
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

void rigidbody::setRot(vec2 rot)
{
    if(ownerSet)
        owner->setRot(rot);
    return;
}

void rigidbody::setRot(vec3 rot)
{
    if(ownerSet)
        owner->setRot(rot);
    return;
}

OPERATOR void physobject::setRot(double x, double y)
{
    setRot(vec2(x, y));
    return;
}

OPERATOR void physobject::setRot(double x, double y, double z)
{
    setRot(vec3(x, y, z));
    return;
}

void physobject::setRot(vec2 rot)
{
    rotation2D = rot;
}

void physobject::setRot(vec3 rot)
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

void rigidbody::setScale(vec2 scale)
{
    if(ownerSet)
        owner->setScale(scale);
    return;
}

void rigidbody::setScale(vec3 scale)
{
    if(ownerSet)
        owner->setScale(scale);
    return;
}

OPERATOR void physobject::setScale(double x, double y)
{
    setScale(vec2(x, y));
    return;
}

OPERATOR void physobject::setScale(double x, double y, double z)
{
    setScale(vec3(x, y, z));
    return;
}

void physobject::setScale(vec2 scale)
{
    coordinates2D = scale;
}

void physobject::setScale(vec3 scale)
{
    coordinates3D = scale;
}