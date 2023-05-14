/*
*   name: include/graphics/compute.hpp
*   origin: Citrus Engine
*   purpose: Provide matrix types based off GLM
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_COMPUTE_SHADERS_HPP__
#define CITRUS_ENGINE_COMPUTE_SHADERS_HPP__

#define GLM_FORCE_INTRINSICS true
#define GLM_FORCE_ALIGNED true
#define GLM_FORCE_RADIANS true

#include <glm/glm.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#undef GLM_FORCE_INTRINSICS
#undef GLM_FORCE_ALIGNED
#undef GLM_FORCE_RADIANS

namespace engine
{
	namespace render
	{
		using Matrix2x2 = glm::mat2;
		using Matrix3x3 = glm::mat3;
		using Matrix4x4 = glm::mat4;
	}
}

#endif