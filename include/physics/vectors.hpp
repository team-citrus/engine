#ifndef CITRUS_ENGINE_VECTORS_HPP__
#define CITRUS_ENGINE_VECTORS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"

namespace engine
{
    namespace physics
    {
        // TODO: add advanced Vector math functions

        // Essentially two doubles to make our lives easier with physics
        class vec2
        {
        public:
            double x;
            double y;

            // Constructors

            vec2()
            {
                x = y = 0;
            }
            vec2(double cx, double cy)
            {
                x = cx;
                y = cy;
            }

            // Operators

            OPERATOR vec2 operator+(vec2 &vec)
            {
                return vec2(x + vec.x, y + vec.y);
            }
            OPERATOR vec2 operator+(double x)
            {
                return *this + vec2(x, x);
            }
            OPERATOR vec2 operator-(vec2 &vec)
            {
                return vec2(x - vec.x, y - vec.y);
            }
            OPERATOR vec2 operator-(double x)
            {
                return *this - vec2(x, x);
            }
            OPERATOR vec2 operator*(vec2 &vec)
            {
                return vec2(x * vec.x, y * vec.y);
            }
            OPERATOR vec2 operator*(double x)
            {
                return *this * vec2(x, x);
            }
            OPERATOR vec2 operator/(vec2 &vec)
            {
                return vec2(x / vec.x, y / vec.y);
            }
            OPERATOR vec2 operator/(double x)
            {
                return *this / vec2(x, x);
            }
        };

        // Essentially three doubles to make our lives easier with physics
        class vec3
        {
        public:
            double x;
            double y;
            double z;

            // Constructors

            vec3()
            {
                x = y = z = 0;
            }
            vec3(double cw, double cx, double cy, double cz)
            {
                x = cx;
                y = cy;
                z = cz;
            }

            // Operators

            OPERATOR vec3 operator+(vec3 &vec)
            {
                return vec3(x + vec.x, y + vec.y, z + vec.z);
            }
            OPERATOR vec3 operator+(double x)
            {
                return *this + vec3(x, x, x);
            }
            OPERATOR vec3 operator-(vec3 &vec)
            {
                return vec3(x - vec.x, y - vec.y, z - vec.z);
            }
            OPERATOR vec3 operator-(double x)
            {
                return *this - vec4(x, x, x, x);
            }
            OPERATOR vec3 operator*(vec3 &vec)
            {
                return vec3(x * vec.x, y * vec.y, z * vec.z);
            }
            OPERATOR vec3 operator*(double x)
            {
                return *this * vec3(x, x, x);
            }
            OPERATOR vec3 operator/(vec3 &vec)
            {
                return vec3(x / vec.x, y / vec.y, z / vec.z);
            }
            OPERATOR vec3 operator/(double x)
            {
                return *this / vec3(x, x, x);
            }
        };

        // Essentially four doubles to make our lives easier with physics
        class vec4
        {
        public:
            double w;
            double x;
            double y;
            double z;

            // Constructors

            vec4()
            {
                w = x = y = z = 0;
            }
            vec4(double cw, double cx, double cy, double cz)
            {
                w = cw;
                x = cx;
                y = cy;
                z = cz;
            }

            // Operators

            OPERATOR vec4 operator+(vec4 &vec)
            {
                return vec4(w + vec.w, x + vec.x, y + vec.y, z + vec.z);
            }
            OPERATOR vec4 operator+(double x)
            {
                return *this + vec4(x, x, x, x);
            }
            OPERATOR vec4 operator-(vec4 &vec)
            {
                return vec4(w - vec.w, x - vec.x, y - vec.y, z - vec.z);
            }
            OPERATOR vec4 operator-(double x)
            {
                return *this - vec4(x, x, x, x);
            }
            OPERATOR vec4 operator*(vec4 &vec)
            {
                return vec4(w * vec.w, x * vec.x, y * vec.y, z * vec.z);
            }
            OPERATOR vec4 operator*(double x)
            {
                return *this * vec4(x, x, x, x);
            }
            OPERATOR vec4 operator/(vec4 &vec)
            {
                return vec4(w / vec.w, x / vec.x, y / vec.y, z / vec.z);
            }
            OPERATOR vec4 operator/(double x)
            {
                return *this / vec4(x, x, x, x);
            }

            // TODO: add quaternion functions
        };

        // Added for code clarity
        typedef vec4 quaternion;
    };
};

#endif