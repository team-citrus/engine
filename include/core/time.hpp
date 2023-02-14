/*
*   name: include/core/scene_int.hpp
*   origin: Citrus Engine
*   purpose: Provide getFrameDelta(), getPhysicsDelta()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_TIME_HPP__
#define CITRUS_ENGINE_TIME_HPP__

namespace engine
{
    float getFrameDelta();
    float getFrameDeltaD();

    namespace physics
    {
        float getPhysicsDelta();
        float getPhysicsDeltaD();
    }
}

#endif