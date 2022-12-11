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
#include "include/physics/vectors.hpp"
#include "include/physics/physobject.hpp"
#include "include/physics/rigidbody.hpp"

using namespace engine;
using namespace physics;

// Advanced physics stuff

/*	Sets the owner of the physobject.
*	Assumed to be called when being initialized into the scene.
*	Locks so it can't be called twice.
*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
*	@param Owner Pointer to the owner
*/
void rigidbody::setOwner(physobject *Owner)
{
    if(!ownerSet)
        owner = Owner;
    return;
}

/*	Overrides the owner of the physobject.
*	Unlocks the owner of the physobject.
*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
*	@param Owner Pointer to the owner
*/
void rigidbody::overrideOwner(physobject *Owner)
{
    ownerSet = false;
    owner = Owner;
}
				
/*	Gets the owner, -1 if not set
*	@warning FOR INTERNAL OR EXPERT USE ONLY, CAN CAUSE SEVERE ISSUES
*/
physobject *rigidbody::getOwner()
{
    if(ownerSet)
        return owner;
    else
        return (physobject*)((uintptr_t)(-1));
}