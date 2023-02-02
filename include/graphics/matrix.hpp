/*
*   name: include/graphics/compute.hpp
*   origin: Citrus Engine
*   purpose: Provide matrix types based off GLM
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPUTE_SHADERS_HPP__
#define CITRUS_ENGINE_COMPUTE_SHADERS_HPP__

#include <glm/glm.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace engine
{
    namespace render
    {
        typedef glm::mat2 matrix2x2;
        typedef glm::mat3 matrix3x3;
        typedef glm::mat4 matrix4x4;
    }
}

#endif