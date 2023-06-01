/*
 *   name: include/core/transform.hpp
 *   origin: Citrus Engine
 *   purpose: Provide engine::transform2D, and engine::transform3D
 *   author: https://github.com/ComradeYellowCitrusFruit
 *   license: LGPL-3.0-only
 */

#ifndef CITRUS_ENGINE_TRANSFORM_HPP__
#define CITRUS_ENGINE_TRANSFORM_HPP__

#include <glm/glm.hpp>
#include "../core/extensions.h"
#include "../core/component.hpp"

namespace engine
{
	using Float2 = glm::vec2;
	using Float3 = glm::vec3;
	using Float4 = glm::vec4;
	using Quaternion = glm::quat;
	using Quat = Quaternion;

	class Transform2D : public Component
	{
	public:
		Float2 position;

		float rotation;

		Float2 scale;

		Transform2D()
		{
			position = Float2(0, 0);
			rotation = 0;
			scale = Float2(1, 1);
		}

		Transform2D(Float2 p)
		{
			position = p;
			rotation = 0;
			scale = Float2(1, 1);
		}

		Transform2D(Float2 p, float r)
		{
			position = position;
			rotation = r;
			scale = Float2(1, 1);
		}

		Transform2D(Float2 p, float r, Float2 s)
		{
			position = p;
			rotation = r;
			scale = s;
		}

		OPERATOR Transform2D &operator=(Transform2D &otra)
		{
			position = otra.position;
			rotation = otra.rotation;
			scale = otra.scale;
		}

		OPERATOR bool operator==(Transform2D &otra)
		{
			return (position == otra.position) && (rotation == otra.rotation) && (scale == otra.scale);
		}
	};

	class Transform3D : public Component
	{
	public:
		Float3 position;
		Quaternion rotation;
		Float3 scale;

		Transform3D()
		{
			position = Float3(0, 0, 0);
			rotation = Quaternion(Float3(0, 0, 0));
			scale = Float3(1, 1, 1);
		}

		Transform3D(Float3 p)
		{
			position = p;
			rotation = Quaternion(Float3(0, 0, 0));
			scale = Float3(1, 1, 1);
		}

		Transform3D(Float3 p, Float3 euler)
		{
			position = p;
			rotation = Quaternion(euler);
			scale = Float3(1, 1, 1);
		}

		Transform3D(Float3 p, Quaternion q)
		{
			position = p;
			rotation = q;
			scale = Float3(1, 1, 1);
		}

		Transform3D(Float3 p, Float3 euler, Float3 s)
		{
			position = p;
			rotation = Quaternion(euler);
			scale = s;
		}

		Transform3D(Float3 p, Quaternion q, Float3 s)
		{
			position = p;
			rotation = q;
			scale = s;
		}

		OPERATOR Transform3D &operator=(Transform3D &otra)
		{
			position = otra.position;
			rotation = otra.rotation;
			scale = otra.scale;
		}

		OPERATOR bool operator==(Transform3D &otra)
		{
			return (position == otra.position) && (rotation == otra.rotation) && (scale == otra.scale);
		}

		// TODO: Euler angles

		virtual void awake()
		{
			return;
		}
		virtual void start()
		{
			return;
		}
		virtual void update()
		{
			return;
		}

		virtual void fixedUpdate()
		{
			return;
		}
		virtual void onTriggerEnter()
		{
			return;
		}
		virtual void onTriggerStay()
		{
			return;
		}
		virtual void onTriggerExit()
		{
			return;
		}
	};
};

#endif