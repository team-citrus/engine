#ifndef CITRUS_ENGINE_PHYSICS_SIMULATION_HPP__
#define CITRUS_ENGINE_PHYSICS_SIMULATION_HPP__

#include <box2d/box2d.h>
#include <btDiscreteDynamicsWorld.h>

namespace engine
{
namespace physics
{
    namespace core
    {
        // The environment of a physics simulation, as a class
        class simulation
        {
            private:
                // Is the simulation 3D?
                bool is3D;
                
                // Timestep for the simulation 
                float timestep;
                
                /*  The corresponding worlds for 2d and 3d simulations
                *   Set to an annoymus union to save memory
                */
                union
                {
                    b2World sim2D;
                    btDiscreteDynamicsWorld sim3D;
                };

                /* TODO: Add engine::internals::physics::physobject
                std::vector<engine::internals::physics::physobject> objects;
                */

            public:

                // Constructors

                simulation();
                simulation(bool is3D);
                simulation(bool is3D, float timestep);

                // Getters and setters

                float getTimestep()
                {
                    return this->timestep;
                }
                // @return If anything actually happened.
                bool setTimestep(float timestep);

                // @return True if 3D, false if 2D
                bool checkDimensions()
                {
                    return this->is3D;
                }
        };
    };
};
};

#endif