/*
*   name: include/physics/vectors.hpp
*   origin: Citrus Engine
*   purpose: Provides typedefs for the glm vector types
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VECTORS_HPP__
#define CITRUS_ENGINE_VECTORS_HPP__

#define GLM_FORCE_INTRINSICS true
#define GLM_FORCE_ALIGNED true
#define GLM_FORCE_RADIANS true

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#undef GLM_FORCE_INTRINSICS
#undef GLM_FORCE_ALIGNED
#undef GLM_FORCE_RADIANS

namespace engine
{
	namespace physics
	{
		// C++ style typedefs,
		using Vec2 = glm::vec2;
		using Vec3 = glm::vec3;
		using Vec4 = glm::vec4;
		using Quat = glm::quat;
		using Quaternion = Quat;

		// TODO: Wrapper functions
	};
};

#endif