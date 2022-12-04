#ifndef CITRUS_ENGINE_PHYSICS_MAIN_HPP__
#define CITRUS_ENGINE_PHYSICS_MAIN_HPP__

#include <vector>
#include "include/physics/sim.hpp"

namespace engine
{
namespace internals
{
	namespace physics
	{
        using namespace physics;

        // The main physics simulation
        core::simulation mainSim;

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
        int queue(core::simulation *sim);

        /*  Removes a simulation from the queue
        *   @param sim Simulation to remove from the queue
        *   @return Any errors that may arise
        */
        int dequeue(core::simulation *sim);

        // The queue
        std::vector<core::simulation*> simQueue;
    };
};
};
#endif