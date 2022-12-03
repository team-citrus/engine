#ifndef CITRUS_ENGINE_PHYSICS_SIMULATION_HPP__
#define CITRUS_ENGINE_PHYSICS_SIMULATION_HPP__

#include <vector>
#include <box2d/box2d.h>
#include <btDiscreteDynamicsWorld.h>
#include "include/physics/physobject.hpp"

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

				std::vector<engine::physics::physobject> objects;

				// Is the simulation queued?
				bool queued;

			public:

				// Constructors

				simulation();
				simulation(bool is3D);
				simulation(bool is3D, float timestep);

				// Getters and setters

				float getTimestep();
				// @return If anything actually happened.
				bool setTimestep(float timestep);

				// @return True if 3D, false if 2D
				bool checkDimensions();

				/*  Calculate the simulation for a single timestep.
				*   @return Any error codes that may arise
				*/
				int step();

				// Add this simulation to the main queue, won't do anything if it is already queued.
				void queue();

				// Remove this simulation from the main queue, won't do anything if it is already queued.
				void dequeue();

				// Get a pointer to the simulation for internal use.
				void *getPtr();
		};
	};
};
};

#endif