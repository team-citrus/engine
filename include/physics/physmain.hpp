/*
*   name: include/physics/physmain.hpp
*   origin: Citrus Engine
*   purpose: Provides the main function for physics
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_PHYSICS_MAIN_HPP__
#define CITRUS_ENGINE_PHYSICS_MAIN_HPP__

#include <box2d/box2d.h>
#include <btBulletDynamicsCommon.h>
#include "core/vector.hpp"
#include "physics/physobject.hpp"

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
        void Init(bool 2D);

        // Deconstruct physics
        void Fini();

        /*  Steps the main physics simulation
        *   @warning THIS SHOULD ONLY BE CALLED WITHIN physmain()
        *   DO NOT CALL IT ANYWHERE ELSE UNLESS YOU WANT TO SERIOUSLY MESS THINGS UP.
        *   @return Any error codes that might arrise
        */
        int step();

        // State of physics
        class PHYS_STATE
        {
            public:
            bool is2D;
            int stepRate;
            union
            {
                b2World world2D;
                btDiscreteDynamicsWorld world3D;
            };
            union
            {
                Vector<engine::physics::physobject2D> objs2D;
                Vector<engine::physics::physobject3D> objs3D;
            };
        }

        // The physics state
        PHYS_STATE state;
    };
};
};
#endif