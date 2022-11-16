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

vec4::vec4(double cx, double cy, double cz, double cw)
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

vec2 vec2::operator+(vec2 &obj)
{
    vec2 ret = *this;
    ret.x += obj.x;
    ret.y += obj.y;
    return ret;
}

vec2 vec2::operator-(vec2 &obj)
{
    vec2 ret = *this;
    ret.x -= obj.x;
    ret.y -= obj.y;
    return ret;
}

vec2 vec2::operator*(vec2 &obj)
{
    vec2 ret = *this;
    ret.x += obj.x;
    ret.y += obj.y;
    return ret;
}

vec2 vec2::operator/(vec2 &obj)
{
    vec2 ret = *this;
    ret.x -= obj.x;
    ret.y -= obj.y;
    return ret;
}

void vec2::operator+=(vec2 &obj)
{
    *this = *this + obj;
}

void vec2::operator-=(vec2 &obj)
{
    *this = *this - obj;
}

void vec2::operator*=(vec2 &obj)
{
    *this = *this * obj;
}

void vec2::operator/=(vec2 &obj)
{
    *this = *this / obj;
}

vec2 vec2::operator+(double x)
{
    vec2 ret = *this;
    ret.x += x;
    ret.y += x;
    return ret;
}

vec2 vec2::operator-(double x)
{
    vec2 ret = *this;
    ret.x -= x;
    ret.y -= x;
    return ret;
}

vec2 vec2::operator*(double x)
{
    vec2 ret = *this;
    ret.x *= x;
    ret.y *= x;
    return ret;
}

vec2 vec2::operator/(double x)
{
    vec2 ret = *this;
    ret.x /= x;
    ret.y /= x;
    return ret;
}

void vec2::operator+=(double x)
{
    *this = *this + x;
}

void vec2::operator-=(double x)
{
    *this = *this - x;
}

void vec2::operator*=(double x)
{
    *this = *this * x;
}

void vec2::operator/=(double x)
{
    *this = *this / x;
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
    return *this + ivec2(x, x).toVec2();
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

//  vec3 operators

vec3 vec3::operator+(vec3 &obj)
{
    vec3 ret = *this;
    ret.x += obj.x;
    ret.y += obj.y;
    ret.z += obj.z;
    return ret;
}

vec3 vec3::operator-(vec3 &obj)
{
    vec3 ret = *this;
    ret.x -= obj.x;
    ret.y -= obj.y;
    ret.z -= obj.z;
    return ret;
}

vec3 vec3::operator*(vec3 &obj)
{
    vec3 ret = *this;
    ret.x *= obj.x;
    ret.y *= obj.y;
    ret.z *= obj.z;
    return ret;
}

vec3 vec3::operator*(vec3 &obj)
{
    vec3 ret = *this;
    ret.x /= obj.x;
    ret.y /= obj.y;
    ret.z /= obj.z;
    return ret;
}

void vec3::operator+=(vec3 &obj)
{
    *this = *this + obj;
}

void vec3::operator-=(vec3 &obj)
{
    *this = *this - obj;
}

void vec3::operator*=(vec3 &obj)
{
    *this = *this * obj;
}

void vec3::operator/=(vec3 &obj)
{
    *this = *this / obj;
}

vec3 vec3::operator+(double x)
{
    vec3 ret = *this;
    ret.x += x;
    ret.y += x;
    ret.z += x;
    return ret;
}

vec3 vec3::operator-(double x)
{
    vec3 ret = *this;
    ret.x -= x;
    ret.y -= x;
    ret.z -= x;
    return ret;
}

vec3 vec3::operator*(double x)
{
    vec3 ret = *this;
    ret.x *= x;
    ret.y *= x;
    ret.z *= x;
    return ret;
}

vec3 vec3::operator+(double x)
{
    vec3 ret = *this;
    ret.x /= x;
    ret.y /= x;
    ret.z /= x;
    return ret;
}

void vec3::operator+=(double x)
{
    *this = *this + x;
}

void vec3::operator-=(double x)
{
    *this = *this - x;
}

void vec3::operator*=(double x)
{
    *this = *this * x;
}

void vec3::operator/=(double x)
{
    *this = *this / x;
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
    return *this + ivec3(x, x, x).toVec3();
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

//  vec4 operators

vec4 vec4::operator+(vec4 &obj)
{
    vec4 ret = *this;
    ret.w += obj.w;
    ret.x += obj.x;
    ret.y += obj.y;
    ret.z += obj.z;
    return ret;
}

vec4 vec4::operator-(vec4 &obj)
{
    vec4 ret = *this;
    ret.w -= obj.w;
    ret.x -= obj.x;
    ret.y -= obj.y;
    ret.z -= obj.z;
    return ret;
}

vec4 vec4::operator*(vec4 &obj)
{
    vec4 ret = *this;
    ret.w *= obj.w;
    ret.x *= obj.x;
    ret.y *= obj.y;
    ret.z *= obj.z;
    return ret;
}

vec4 vec4::operator/(vec4 &obj)
{
    vec4 ret = *this;
    ret.w /= obj.w;
    ret.x /= obj.x;
    ret.y /= obj.y;
    ret.z /= obj.z;
    return ret;
}

void vec4::operator+=(vec4 &obj)
{
    *this = *this + obj;
}

void vec4::operator-=(vec4 &obj)
{
    *this = *this - obj;
}

void vec4::operator*=(vec4 &obj)
{
    *this = *this * obj;
}

void vec4::operator/=(vec4 &obj)
{
    *this = *this / obj;
}

vec4 vec4::operator+(double x)
{
    vec4 ret = *this;
    ret.w += x;
    ret.x += x;
    ret.y += x;
    ret.z += x;
    return ret;
}

vec4 vec4::operator-(double x)
{
    vec4 ret = *this;
    ret.w -= x;
    ret.x -= x;
    ret.y -= x;
    ret.z -= x;
    return ret;
}

vec4 vec4::operator*(double x)
{
    vec4 ret = *this;
    ret.w *= x;
    ret.x *= x;
    ret.y *= x;
    ret.z *= x;
    return ret;
}

vec4 vec4::operator/(double x)
{
    vec4 ret = *this;
    ret.w /= x;
    ret.x /= x;
    ret.y /= x;
    ret.z /= x;
    return ret;
}

void vec4::operator+=(double x)
{
    *this = *this + x;
}

void vec4::operator-=(double x)
{
    *this = *this - x;
}

void vec4::operator*=(double x)
{
    *this = *this * x;
}

void vec4::operator/=(double x)
{
    *this = *this / x;
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