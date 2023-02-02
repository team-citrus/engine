/*
*   name: include/graphics/compute.hpp
*   origin: Citrus Engine
*   purpose: Provide API for compute shaders
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPUTE_SHADERS_HPP__
#define CITRUS_ENGINE_COMPUTE_SHADERS_HPP__

#include "core/extensions.hpp"

namespace engine
{
    namespace render
    {
        class computeShader
        {
            union
            {
                VkShaderModule vkMod;
                // TODO: OpenGL representation
            };
            public:
            computeShader(const char *shader);
            ~computeShader();
            OPERATOR void operator()()
            {
                dispatch();
            }
            void dispatch();

            // TODO: Args and stuff
        };
    }
}


#endif