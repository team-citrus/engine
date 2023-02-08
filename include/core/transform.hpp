/*
*   name: include/core/transform.hpp
*   origin: Citrus Engine
*   purpose: Provide engine::transform2D, and engine::transform3D
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_TRANSFORM_HPP__
#define CITRUS_ENGINE_TRANSFORM_HPP__

#include "core/extensions.h"
#include "core/component.hpp"
#include "physics/vectors.hpp"

namespace engine
{
    typedef physics::vec2 float2;
    typedef physics::vec3 float3;
    typedef physics::vec4 float4;

    class transform2D : component
    {
        public:
            union
            {
                struct
                {
                    float x;
                    float y;
                };
                float2 vec;
            } position;

            union
            {
                struct
                {
                    float x;
                    float y;
                };
                float2 vec;
            } rotation;

            union
            {
                struct
                {
                    float x;
                    float y;
                };
                float2 vec;
            } scale;

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
    }

    class transform3D : component
    {
        public:
            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                };
                float3 vec;
            } position;

            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                };
                float3 vec;
            } rotation;

            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                };
                float3 vec;
            } scale;

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
    }
};

#endif