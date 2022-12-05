#include <cstdlib>
#include <box2d/box2d.h>
#include "include/physics/vectors.hpp"
#include "include/physics/physobject.hpp"
#include "include/physics/rigidbody.hpp"

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
