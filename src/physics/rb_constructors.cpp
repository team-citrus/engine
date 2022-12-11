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
