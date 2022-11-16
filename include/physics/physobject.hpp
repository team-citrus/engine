#ifndef CITRUS_ENGINE_PHYSICS_OBJECTS_HPP__
#define CITRUS_ENGINE_PHYSICS_OBJECTS_HPP__

#include "include/physics/vectors.hpp"

namespace engine
{
    namespace physics
    {
        /*  The underlying class of anything that needs physics
        *   This is directly interfaced by the physics API frequently, and is the primary object for physics code
        */
        class physobject
        {
            private:

                // Transform is some anonymous unions to save memory and make our lives easier

                // Cordinates, right handed X coordinate
                union
                {
                    engine::physics::vec3 coordinates3D;
                    engine::physics::vec2 coordinates2D;
                };

                // Rotation, pitch, yaw, and roll form, technically is only used for quaternion conversions in 3d mode
                union
                {
                    engine::physics::vec3 rotation3D;
                    engine::physics::vec2 rotation2D;
                };

                // Scale, like lens magnification, negative values invert the object on the axis
                union
                {
                    engine::physics::vec3 scale3D;
                    engine::physics::vec2 scale2D;
                };

                // QUATERNIONS
                engine::physics::vec4 quaternion;

                /*  TODO: Add engine::physics::rigidbody, engine::physics::collider, and engine::object
                *   bool usesRigidbody;
                *   int coordinateLocks;
                *   int rotationLocks;
                *
                *   engine::physics::collider *colliders;
                *   engine::physics::rigidbody rigidbody;
                *   engine::object *owner;
                */

            public:
                // Constructors
                physobject();
                physobject(vec2 pos);
                physobject(vec2 pos, vec2 rot);
                physobject(vec2 pos, vec2 rot, vec2 scale);
                physobject(vec3 pos);
                physobject(vec3 pos, vec3 rot);
                physobject(vec3 pos, vec3 rot, vec3 scale);
                
                // Lock stuff

                // Set position locks
                void setPosLocks(int locks);
                // Get current position locks
                int getPosLocks();
                // Toggle possition locks
                void togglePosLocks(int locks);
                // Clear position locks
                void clearPosLocks();
                // Set all position locks
                void lockAllPos();

                // Set rotation locks
                void setRotLocks(int locks);
                // Get current position locks
                int getRotLocks();
                // Toggle possition locks
                void toggleRotLocks(int locks);
                // Clear position locks
                void clearRotLocks();
                // Set all position locks
                void lockAllRot();

                // Lock everything
                void lockAll();
        };
    };
};

#endif