/*
*   name: include/graphics/camera.hpp
*   origin: Citrus Engine
*   purpose: Provide a class for the camera
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_CAMERA_HPP__
#define CITRUS_ENGINE_CAMERA_HPP__

#include "../graphics/matrix.hpp"
#include "../core/component.hpp"

namespace engine
{
	namespace render
	{
		class Camera : Component
		{
			public:
			Matrix4x4 getViewMatrix();
			float focalLength;

			union
			{
				float fov;
				float fieldOfView;
			};
			
			bool isOrthographic;
			float orthographicSize;

			// TODO: Stuff
		}
	}
}

#endif