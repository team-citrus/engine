#include "core/scene_int.hpp"
#include "core/time.hpp"

namespace engine
{
    float getFrameDelta()
    {
        return ((float)internals::frameDelta/100.0F);
    }

    float getFrameDeltaD()
    {
        return ((double)internals::frameDelta/100.0);
    }

    namespace physics
    {
        float getPhysicsDelta()
        {
            return ((float)internals::physics::physicsDelta/100.0F);
        }

        float getPhysicsDeltaD()
        {
            return ((double)internals::physics::physicsDelta/100.0);
        }
    }
}