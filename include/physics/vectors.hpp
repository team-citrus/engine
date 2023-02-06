/*
*   name: include/physics/vectors.hpp
*   origin: Citrus Engine
*   purpose: Provides typedefs for the glm vector types
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VECTORS_HPP__
#define CITRUS_ENGINE_VECTORS_HPP__

#define GLM_FORCE_SSE2 1
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine
{
    namespace physics
    {
        // Good ol' typedefs
        
        typedef glm::vec2 vec2;
        typedef glm::vec3 vec3;
        typedef glm::vec4 vec4;
        typedef glm::quat quat;
        typedef quat quaternion;
    };
};

#endif