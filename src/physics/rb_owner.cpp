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