/*
*   name: src/physics/queue.cpp
*   origin: Citrus Engine
*   purpose: Provides some of the code for the queue functions in include/physics/physmain.hpp
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
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