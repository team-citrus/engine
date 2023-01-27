/*
*   name: src/physics/rb_constructors.cpp
*   origin: Citrus Engine
*   purpose: Provides the constructors for the engine::physics::rigidbody class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include <cstdlib>
#include <box2d/box2d.h>
#include "physics/vectors.hpp"
#include "physics/physobject.hpp"
#include "physics/rigidbody.hpp"

using namespace engine;
using namespace physics;

rigidbody::rigidbody()
{
    owner = (physobject*)NULL;
    awake = false;
    ownerSet = false;
}

rigidbody::rigidbody(physobject *Owner)
{
    owner = owner;
    ownerSet = true;
    awake = false;
}
