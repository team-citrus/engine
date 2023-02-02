/*
*   name: include/graphics/compute.hpp
*   origin: Citrus Engine
*   purpose: Provide API for shaders
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPUTE_SHADERS_HPP__
#define CITRUS_ENGINE_COMPUTE_SHADERS_HPP__

#include <vulkan.h>
#include <gl/gl.n>

namespace engine
{
    namespace render
    {
        class shader
        {
            union
            {
                VkShaderModule vkMod;
                // TODO: OpenGL representation
            };
            public:
            shader(const char *shader);
            ~shader();
        };
    }
}

#endif