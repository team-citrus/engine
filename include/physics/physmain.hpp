/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_PHYSICS_MAIN_HPP__
#define CITRUS_ENGINE_PHYSICS_MAIN_HPP__

#include "include/core/vector.hpp"
#include "include/physics/sim.hpp"

#define INTERNALS_PHYSICS_DEQUEUE_ERR_NOT_FOUND -1
#define INTERNALS_PHYSICS_QUEUE_ERR_ALREADY_QUEUED -1

namespace engine
{
namespace internals
{
	namespace physics
	{
        using namespace physics;

        // The main physics simulation
        extern core::simulation mainSim;

        // Initalize physics
        void Init();

        // Deconstruct physics to prepare for shutdown
        void Fini();

        /*  Steps the main physics simulation
        *   @warning THIS SHOULD ONLY BE CALLED WITHIN THE MAIN EVENT LOOP.
        *   DO NOT CALL IT ANYWHERE ELSE UNLESS YOU WANT TO SERIOUSLY MESS THINGS UP.
        *   @return Any error codes that might arrise
        */
        int Main();

        /*  Queues a simulation
        *   @param sim Simulation to queue
        *   @return Any errors that may arise
        */
        int queue(physics::core::simulation *sim);

        /*  Removes a simulation from the queue
        *   @param sim Simulation to remove from the queue
        *   @return Any errors that may arise
        */
        int dequeue(physics::core::simulation *sim);

        // The queue
        extern Vector<physics::core::simulation*> simQueue;
    };
};
};
#endif