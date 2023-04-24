/*
*   name: include/graphics/compute.hpp
*   origin: Citrus Engine
*   purpose: Provide API for shaders
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPUTE_SHADERS_HPP__
#define CITRUS_ENGINE_COMPUTE_SHADERS_HPP__

#include <cstddef>

namespace engine
{
	namespace render
	{
		class Shader
		{
			size_t id;
			public:
			Shader(const char *shader);
			~Shader();
		};
	}
}

#endif