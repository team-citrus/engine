/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#include "include/physics/physmain.hpp"
#include "include/physics/sim.hpp"
#include "include/core/vector.hpp"

using namespace engine;

internals::physics::Vector<physics::core::simulation*> simQueue;

int internals::physics::queue(physics::core::simulation *sim)
{
    int i;
    for(i = 0; i < simQueue.getCount(); i++)
    {
        if(simQueue[i] == sim)
            return INTERNALS_PHYSICS_QUEUE_ERR_ALREADY_QUEUED;
    }
    simQueue.push(sim);
    return 0;
}

int internals::physics::dequeue(physics::core::simulation *sim)
{
    for(int i = 0; i < simQueue.getCount(); i++)
    {
        if(simQueue[i] == sim)
        {
            simQueue.rm(i);
            return 0;
        }
    }
    return INTERNALS_PHYSICS_DEQUEUE_ERR_NOT_FOUND;
}

void physics::core::simulation::queue()
{
    if(!queued)
        internals::physics::queue(this);
    queued = true;
    return;
}

void physics::core::simulation::dequeue()
{
    if(queued)
        internals::physics::dequeue(this);
    queued = false;
    return;
}