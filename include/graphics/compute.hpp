/*
*   name: include/graphics/compute.hpp
*   origin: Citrus Engine
*   purpose: Provide API for compute shaders
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPUTE_SHADERS_HPP__
#define CITRUS_ENGINE_COMPUTE_SHADERS_HPP__

#include "../core/extensions.h"

namespace engine
{
	namespace render
	{
		class ComputeShader
		{
			size_t id;
			public:
			ComputeShader(const char *shader);
			~ComputeShader();
			OPERATOR void operator(int x, int y, int z)()
			{
				dispatch(x, y, z);
			}
			void dispatch(int x, int y, int z);

			// TODO: Args and stuff
		};
	}
}


#endif