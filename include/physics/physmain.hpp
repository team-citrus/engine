/*
*   name: include/physics/physmain.hpp
*   origin: Citrus Engine
*   purpose: Provides the main function for physics
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
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

        // Initalize physics
        void Init();

        // Deconstruct physics to prepare for shutdown
        void Fini();

        /*  Steps the main physics simulation
        *   @warning THIS SHOULD ONLY BE CALLED WITHIN THE MAIN EVENT LOOP.
        *   DO NOT CALL IT ANYWHERE ELSE UNLESS YOU WANT TO SERIOUSLY MESS THINGS UP.
        *   @return Any error codes that might arrise
        */
        int step();
    };
};
};
#endif