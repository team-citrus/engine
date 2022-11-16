#ifndef CITRUS_ENGINE_VECTORS_HPP__
#define CITRUS_ENGINE_VECTORS_HPP__

#include <cstdint>

namespace engine
{
    namespace physics
    {
        // Essentially two doubles to make our lives easier with physics
        class vec2
        {
            public:
                double x;
                double y;

                // Constructors

                vec2();
                vec2(double cx, double cy);

                // Convert to a ivec2
                ivec2 toIVec2();

                // Operators

                vec2 operator+(vec2 &vec);
                vec2 operator+(double x);
                vec2 operator+(int x);
                vec2 operator-(vec2 &vec);
                vec2 operator-(double x);
                vec2 operator-(int x);
                vec2 operator*(vec2 &vec);
                vec2 operator*(double x);
                vec2 operator*(int x);
                vec2 operator/(vec2 &vec);
                vec2 operator/(double x);
                vec2 operator/(int x);
                void operator+=(vec2 &vec);
                void operator+=(double x);
                void operator+=(int x);
                void operator-=(vec2 &vec);
                void operator-=(double x);
                void operator-=(int x);
                void operator*=(vec2 &vec);
                void operator*=(double x);
                void operator*=(int x);
                void operator/=(vec2 &vec);
                void operator/=(double x);
                void operator/=(int x);
        };

        // Essentially three doubles to make our lives easier with physics
        class vec3
        {
            public:
                double x;
                double y;
                double z;

                // Constructors

                vec3();
                vec3(double cx, double cy, double cz);

                // Convert to a ivec3
                ivec3 toIVec3();

                // Operators

                vec3 operator+(vec3 &vec);
                vec3 operator+(double x);
                vec3 operator+(int x);
                vec3 operator-(vec3 &vec);
                vec3 operator-(double x);
                vec3 operator-(int x);
                vec3 operator*(vec3 &vec);
                vec3 operator*(double x);
                vec3 operator*(int x);
                vec3 operator/(vec3 &vec);
                vec3 operator/(double x);
                vec3 operator/(int x);
                void operator+=(vec3 &vec);
                void operator+=(double x);
                void operator+=(int x);
                void operator-=(vec3 &vec);
                void operator-=(double x);
                void operator-=(int x);
                void operator*=(vec3 &vec);
                void operator*=(double x);
                void operator*=(int x);
                void operator/=(vec3 &vec);
                void operator/=(double x);
                void operator/=(int x);
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

                vec4();
                vec4(double cx, double cy, double cz, double cw);

                // Convert to a ivec4
                ivec4 toIVec4();

                // Operators

                vec4 operator+(vec4 &vec);
                vec4 operator+(double x);
                vec4 operator+(int x);
                vec4 operator-(vec4 &vec);
                vec4 operator-(double x);
                vec4 operator-(int x);
                vec4 operator*(vec4 &vec);
                vec4 operator*(double x);
                vec4 operator*(int x);
                vec4 operator/(vec4 &vec);
                vec4 operator/(double x);
                vec4 operator/(int x);
                void operator+=(vec4 &vec);
                void operator+=(double x);
                void operator+=(int x);
                void operator-=(vec4 &vec);
                void operator-=(double x);
                void operator-=(int x);
                void operator*=(vec4 &vec);
                void operator*=(double x);
                void operator*=(int x);
                void operator/=(vec4 &vec);
                void operator/=(double x);
                void operator/=(int x);
        };

        // Essentially two int64_ts to make our lives easier with physics
        class ivec2
        {
            public:
                int64_t x;
                int64_t y;

                // Constructors

                ivec2();
                ivec2(int64_t cx, int64_t cy);

                // Convert to a vec2
                vec2 toVec2();

                // Operators

                ivec2 operator+(ivec2 &vec);
                ivec2 operator+(double x);
                ivec2 operator+(int x);
                ivec2 operator-(ivec2 &vec);
                ivec2 operator-(double x);
                ivec2 operator-(int x);
                ivec2 operator*(ivec2 &vec);
                ivec2 operator*(double x);
                ivec2 operator*(int x);
                ivec2 operator/(ivec2 &vec);
                ivec2 operator/(double x);
                ivec2 operator/(int x);
                void operator+=(ivec2 &vec);
                void operator+=(double x);
                void operator+=(int x);
                void operator-=(ivec2 &vec);
                void operator-=(double x);
                void operator-=(int x);
                void operator*=(ivec2 &vec);
                void operator*=(double x);
                void operator*=(int x);
                void operator/=(ivec2 &vec);
                void operator/=(double x);
                void operator/=(int x);
        };

        // Essentially three int64_ts to make our lives easier with physics
        class ivec3
        {
            public:
                int64_t x;
                int64_t y;
                int64_t z;

                // Constructors

                ivec3();
                ivec3(int64_t cx, int64_t cy, int64_t cz);

                // Convert to a vec3
                vec3 toVec3();

                // Operators

                ivec3 operator+(ivec3 &vec);
                ivec3 operator+(double x);
                ivec3 operator+(int x);
                ivec3 operator-(ivec3 &vec);
                ivec3 operator-(double x);
                ivec3 operator-(int x);
                ivec3 operator*(ivec3 &vec);
                ivec3 operator*(double x);
                ivec3 operator*(int x);
                ivec3 operator/(ivec3 &vec);
                ivec3 operator/(double x);
                ivec3 operator/(int x);
                void operator+=(ivec3 &vec);
                void operator+=(double x);
                void operator+=(int x);
                void operator-=(ivec3 &vec);
                void operator-=(double x);
                void operator-=(int x);
                void operator*=(ivec3 &vec);
                void operator*=(double x);
                void operator*=(int x);
                void operator/=(ivec3 &vec);
                void operator/=(double x);
                void operator/=(int x);
        };

        // Essentially four int64_ts to make our lives easier with physics
        class ivec4
        {
            public:
                int64_t w;
                int64_t x;
                int64_t y;
                int64_t z;

                // Constructors

                ivec4();
                ivec4(int64_t cw, int64_t cx, int64_t cy, int64_t cz);

                // Convert to a vec4
                vec4 toVec4();

                // Operators

                ivec4 operator+(ivec4 &vec);
                ivec4 operator+(double x);
                ivec4 operator+(int x);
                ivec4 operator-(ivec4 &vec);
                ivec4 operator-(double x);
                ivec4 operator-(int x);
                ivec4 operator*(ivec4 &vec);
                ivec4 operator*(double x);
                ivec4 operator*(int x);
                ivec4 operator/(ivec4 &vec);
                ivec4 operator/(double x);
                ivec4 operator/(int x);
                void operator+=(ivec4 &vec);
                void operator+=(double x);
                void operator+=(int x);
                void operator-=(ivec4 &vec);
                void operator-=(double x);
                void operator-=(int x);
                void operator*=(ivec4 &vec);
                void operator*=(double x);
                void operator*=(int x);
                void operator/=(ivec4 &vec);
                void operator/=(double x);
                void operator/=(int x);
        };
    };
};

#endif