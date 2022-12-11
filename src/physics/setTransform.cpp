/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#include <cstdlib>
#include "include/core/extensions.hpp"
#include "include/physics/vectors.hpp"
#include "include/physics/physobject.hpp"
#include "include/physics/rigidbody.hpp"

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