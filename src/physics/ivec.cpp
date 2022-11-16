#include "include/physics/vectors.hpp"

using namespace engine;
using namespace engine::physics;

// Constructors

ivec2::ivec2()
{
    x = 0;
    y = 0;
    return;
}

ivec2::ivec2(int64_t cx, int64_t cy)
{
    x = cx;
    y = cy;
    return;
}

ivec3::ivec3()
{
    x = 0;
    y = 0;
    z = 0;
    return;
}

ivec3::ivec3(int64_t cx, int64_t cy, int64_t cz)
{
    x = cx;
    y = cy;
    z = cz;
    return;
}

ivec4::ivec4()
{
    w = 0;
    x = 0;
    y = 0;
    z = 0;
    return;
}

ivec4::ivec4(int64_t cx, int64_t cy, int64_t cz, int64_t cw)
{
    w = cw;
    x = cx;
    y = cy;
    z = cz;
    return;
}

// vec conversion

vec2 ivec2::toVec2()
{
    return vec2((double)x, (double)y);
}

vec3 ivec3::toVec3()
{
    return vec3((double)x, (double)y, (double)z);
}

vec4 ivec4::toVec4()
{
    return vec4((double)w, (double)x, (double)y, (double)z);
}

// Operators

// ivec2 operators

ivec2 ivec2::operator+(ivec2 &vec)
{
    return ivec2(x + vec.x, y + vec.y);
}

ivec2 ivec2::operator-(ivec2 &vec)
{
    return ivec2(x - vec.x, y - vec.y);
}

ivec2 ivec2::operator*(ivec2 &vec)
{
    return ivec2(x * vec.x, y * vec.y);
}

ivec2 ivec2::operator/(ivec2 &vec)
{
    return ivec2(x / vec.x, y / vec.y);
}

void ivec2::operator+=(ivec2 &vec)
{
    *this = *this + vec;
}

void ivec2::operator-=(ivec2 &vec)
{
    *this = *this - vec;
}

void ivec2::operator*=(ivec2 &vec)
{
    *this = *this * vec;
}

void ivec2::operator/=(ivec2 &vec)
{
    *this = *this / vec;
}

ivec2 ivec2::operator+(double x)
{
    return *this + vec2(x, x).toIVec2();
}

ivec2 ivec2::operator-(double x)
{
    return *this - vec2(x, x).toIVec2();
}

ivec2 ivec2::operator*(double x)
{
    return *this * vec2(x, x).toIVec2();
}

ivec2 ivec2::operator/(double x)
{
    return *this + vec2(x, x).toIVec2();
}

void ivec2::operator+=(double x)
{
    *this = *this + x;
}

void ivec2::operator-=(double x)
{
    *this = *this - x;
}

void ivec2::operator*=(double x)
{
    *this = *this * x;
}

void ivec2::operator/=(double x)
{
    *this = *this + x;
}

ivec2 ivec2::operator+(int x)
{
    return *this + ivec2(x, x);
}

ivec2 ivec2::operator-(int x)
{
    return *this - ivec2(x, x);
}

ivec2 ivec2::operator*(int x)
{
    return *this * ivec2(x, x);
}

ivec2 ivec2::operator/(int x)
{
    return *this + ivec2(x, x);
}

void ivec2::operator+=(int x)
{
    *this += ivec2(x, x);
}

void ivec2::operator-=(int x)
{
    *this -= ivec2(x, x);
}

void ivec2::operator*=(int x)
{
    *this *= ivec2(x, x);
}

void ivec2::operator/=(int x)
{
    *this /= ivec2(x, x);
}

ivec3 ivec3::operator+(ivec3 &vec)
{
    return ivec3(x + vec.x, y + vec.y, z + vec.z);
}

ivec3 ivec3::operator-(ivec3 &vec)
{
    return ivec3(x - vec.x, y - vec.y, z - vec.z);
}

ivec3 ivec3::operator*(ivec3 &vec)
{
    return ivec3(x * vec.x, y * vec.y, z * vec.z);
}

ivec3 ivec3::operator/(ivec3 &vec)
{
    return ivec3(x / vec.x, y / vec.y, z / vec.z);
}

void ivec3::operator+=(ivec3 &vec)
{
    *this = *this + vec;
}

void ivec3::operator-=(ivec3 &vec)
{
    *this = *this - vec;
}

void ivec3::operator*=(ivec3 &vec)
{
    *this = *this * vec;
}

void ivec3::operator/=(ivec3 &vec)
{
    *this = *this / vec;
}

ivec3 ivec3::operator+(double x)
{
    return *this + vec3(x, x, x).toIVec3();
}

ivec3 ivec3::operator-(double x)
{
    return *this - vec3(x, x, x).toIVec3();
}

ivec3 ivec3::operator*(double x)
{
    return *this * vec3(x, x, x).toIVec3();
}

ivec3 ivec3::operator/(double x)
{
    return *this / vec3(x, x, x).toIVec3();
}

void ivec3::operator+=(double x)
{
    *this = *this + x;
}

void ivec3::operator-=(double x)
{
    *this = *this - x;
}

void ivec3::operator*=(double x)
{
    *this = *this * x;
}

void ivec3::operator/=(double x)
{
    *this = *this / x;
}

ivec3 ivec3::operator+(int x)
{
    return *this + ivec3(x, x, x);
}

ivec3 ivec3::operator-(int x)
{
    return *this - ivec3(x, x, x);
}

ivec3 ivec3::operator*(int x)
{
    return *this * ivec3(x, x, x);
}

ivec3 ivec3::operator/(int x)
{
    return *this / ivec3(x, x, x);
}

void ivec3::operator+=(int x)
{
    *this += ivec3(x, x, x);
}

void ivec3::operator-=(int x)
{
    *this -= ivec3(x, x, x);
}

void ivec3::operator*=(int x)
{
    *this *= ivec3(x, x, x);
}

void ivec3::operator/=(int x)
{
    *this /= ivec3(x, x, x);
}