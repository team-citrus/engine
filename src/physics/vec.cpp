#include "include/physics/vectors.hpp"

using namespace engine;
using namespace engine::physics;

// Constructors

vec2::vec2()
{
    x = 0;
    y = 0;
    return;
}

vec2::vec2(double cx, double cy)
{
    x = cx;
    y = cy;
    return;
}

vec3::vec3()
{
    x = 0;
    y = 0;
    z = 0;
    return;
}

vec3::vec3(double cx, double cy, double cz)
{
    x = cx;
    y = cy;
    z = cz;
    return;
}

vec4::vec4()
{
    w = 0;
    x = 0;
    y = 0;
    z = 0;
    return;
}

vec4::vec4(double cw, double cx, double cy, double cz)
{
    w = cw;
    x = cx;
    y = cy;
    z = cz;
    return;
}

// ivec conversions

ivec2 vec2::toIVec2()
{
    ivec2 ivec;
    ivec.x = (int64_t)x;
    ivec.y = (int64_t)y;
    return ivec;
}

ivec3 vec3::toIVec3()
{
    ivec3 ivec;
    ivec.x = (int64_t)x;
    ivec.y = (int64_t)y;
    ivec.z = (int64_t)z;
    return ivec;
}

ivec4 vec4::toIVec4()
{
    ivec4 ivec;
    ivec.w = (int64_t)w;
    ivec.x = (int64_t)x;
    ivec.y = (int64_t)y;
    ivec.z = (int64_t)z;
    return ivec;
}

//  vec2 operators

vec2 vec2::operator+(vec2 &vec)
{
    return vec2(x + vec.x, y + vec.y);
}

vec2 vec2::operator-(vec2 &vec)
{
    return vec2(x - vec.x, y - vec.y);
}

vec2 vec2::operator*(vec2 &vec)
{
    return vec2(x * vec.x, y * vec.y);
}

vec2 vec2::operator/(vec2 &vec)
{
    return vec2(x / vec.x, y / vec.y);
}

void vec2::operator+=(vec2 &vec)
{
    *this = *this + vec;
}

void vec2::operator-=(vec2 &vec)
{
    *this = *this - vec;
}

void vec2::operator*=(vec2 &vec)
{
    *this = *this * vec;
}

void vec2::operator/=(vec2 &vec)
{
    *this = *this / vec;
}

vec2 vec2::operator+(double x)
{
    return *this + vec2(x, x);
}

vec2 vec2::operator-(double x)
{
    return *this - vec2(x, x);
}

vec2 vec2::operator*(double x)
{
    return *this * vec2(x, x);
}

vec2 vec2::operator/(double x)
{
    return *this / vec2(x, x);
}

void vec2::operator+=(double x)
{
    *this += vec2(x, x);
}

void vec2::operator-=(double x)
{
    *this -= vec2(x, x);
}

void vec2::operator*=(double x)
{
    *this += vec2(x, x);
}

void vec2::operator/=(double x)
{
    *this += vec2(x, x);
}

vec2 vec2::operator+(int x)
{
    return *this + ivec2(x, x).toVec2();
}

vec2 vec2::operator-(int x)
{
    return *this - ivec2(x, x).toVec2();
}

vec2 vec2::operator*(int x)
{
    return *this * ivec2(x, x).toVec2();
}

vec2 vec2::operator/(int x)
{
    return *this / ivec2(x, x).toVec2();
}

void vec2::operator+=(int x)
{
    *this += ivec2(x, x).toVec2();
}

void vec2::operator-=(int x)
{
    *this -= ivec2(x, x).toVec2();
}

void vec2::operator*=(int x)
{
    *this *= ivec2(x, x).toVec2();
}

void vec2::operator/=(int x)
{
    *this /= ivec2(x, x).toVec2();
}

// vec3 operators

vec3 vec3::operator+(vec3 &vec)
{
    return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator-(vec3 &vec)
{
    return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 vec3::operator*(vec3 &vec)
{
    return vec3(x * vec.x, y * vec.y, z * vec.z);
}

vec3 vec3::operator/(vec3 &vec)
{
    return vec3(x / vec.x, y / vec.y, z / vec.z);
}

void vec3::operator+=(vec3 &vec)
{
    *this = *this + vec;
}

void vec3::operator-=(vec3 &vec)
{
    *this = *this - vec;
}

void vec3::operator*=(vec3 &vec)
{
    *this = *this * vec;
}

void vec3::operator/=(vec3 &vec)
{
    *this = *this / vec;
}

vec3 vec3::operator+(double x)
{
    return *this + vec3(x, x, x);
}

vec3 vec3::operator-(double x)
{
    return *this - vec3(x, x, x);
}

vec3 vec3::operator*(double x)
{
    return *this * vec3(x, x, x);
}

vec3 vec3::operator/(double x)
{
    return *this / vec3(x, x, x);
}

void vec3::operator+=(double x)
{
    *this += vec3(x, x, x);
}

void vec3::operator-=(double x)
{
    *this -= vec3(x, x, x);
}

void vec3::operator*=(double x)
{
    *this *= vec3(x, x, x);
}

void vec3::operator/=(double x)
{
    *this /= vec3(x, x, x);
}

vec3 vec3::operator+(int x)
{
    return *this + ivec3(x, x, x).toVec3();
}

vec3 vec3::operator-(int x)
{
    return *this - ivec3(x, x, x).toVec3();
}

vec3 vec3::operator*(int x)
{
    return *this * ivec3(x, x, x).toVec3();
}

vec3 vec3::operator/(int x)
{
    return *this / ivec3(x, x, x).toVec3();
}

void vec3::operator+=(int x)
{
    *this += ivec3(x, x, x).toVec3();
}

void vec3::operator-=(int x)
{
    *this -= ivec3(x, x, x).toVec3();
}

void vec3::operator*=(int x)
{
    *this *= ivec3(x, x, x).toVec3();
}

void vec3::operator/=(int x)
{
    *this /= ivec3(x, x, x).toVec3();
}

// vec4 operators

vec4 vec4::operator+(vec4 &vec)
{
    return vec4(w + vec.w, x + vec.x, y + vec.y, z + vec.z);
}

vec4 vec4::operator-(vec4 &vec)
{
    return vec4(w - vec.w, x - vec.x, y - vec.y, z - vec.z);
}

vec4 vec4::operator*(vec4 &vec)
{
    return vec4(w * vec.w, x * vec.x, y * vec.y, z * vec.z);
}

vec4 vec4::operator/(vec4 &vec)
{
    return vec4(w / vec.w, x / vec.x, y / vec.y, z / vec.z);
}

void vec4::operator+=(vec4 &vec)
{
    *this = *this + vec;
}

void vec4::operator-=(vec4 &vec)
{
    *this = *this - vec;
}

void vec4::operator*=(vec4 &vec)
{
    *this = *this * vec;
}

void vec4::operator/=(vec4 &vec)
{
    *this = *this / vec;
}

vec4 vec4::operator+(double x)
{
    return *this + vec4(x, x, x, x);
}

vec4 vec4::operator-(double x)
{
    return *this - vec4(x, x, x, x);
}

vec4 vec4::operator*(double x)
{
    return *this * vec4(x, x, x, x);
}

vec4 vec4::operator/(double x)
{
    return *this / vec4(x, x, x, x);
}

void vec4::operator+=(double x)
{
    *this += vec4(x, x, x, x);
}

void vec4::operator-=(double x)
{
    *this -= vec4(x, x, x, x);
}

void vec4::operator*=(double x)
{
    *this *= vec4(x, x, x, x);
}

void vec4::operator/=(double x)
{
    *this /= vec4(x, x, x, x);
}

vec4 vec4::operator+(int x)
{
    return *this + ivec4(x, x, x, x).toVec4();
}

vec4 vec4::operator-(int x)
{
    return *this - ivec4(x, x, x, x).toVec4();
}

vec4 vec4::operator*(int x)
{
    return *this * ivec4(x, x, x, x).toVec4();
}

vec4 vec4::operator/(int x)
{
    return *this / ivec4(x, x, x, x).toVec4();
}

void vec4::operator+=(int x)
{
    *this += ivec4(x, x, x, x).toVec4();
}

void vec4::operator-=(int x)
{
    *this -= ivec4(x, x, x, x).toVec4();
}

void vec4::operator*=(int x)
{
    *this *= ivec4(x, x, x, x).toVec4();
}

void vec4::operator/=(int x)
{
    *this /= ivec4(x, x, x, x).toVec4();
}