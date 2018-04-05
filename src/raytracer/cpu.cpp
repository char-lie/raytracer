#include <cmath>

#include <CL/cl.hpp>
#include <glm/vec3.hpp>

using glm::vec3;

#include <CL/cl.hpp>

cl_float3 operator*(const cl_float3& x, const float c)
{
    return {c * x.s[0], c * x.s[1], c * x.s[2]};
}

vec3 operator-(const vec3& x, const cl_float3& y)
{
    return {x.x - y.s[0], x.y - y.s[1], x.z - y.s[2]};
}

vec3 operator-(const cl_float3& x, const cl_float3& y)
{
    return {x.s[0] - y.s[0], x.s[1] - y.s[1], x.s[2] - y.s[2]};
}

vec3 operator-(const cl_float3& x, float c)
{
    return {x.s[0] - c, x.s[1] - c, x.s[2] - c};
}

float norm(const vec3& x)
{
    return x.x * x.x + x.y * x.y + x.z * x.z;
}

float distance(const cl_float3& x, const cl_float3& y)
{
    return norm(x - y);
}

float dot(const cl_float3& x, const vec3& y)
{
    return x.s[0] * y.x + x.s[1] * y.y + x.s[2] * y.z;
}

float dot(const cl_float3& x, const cl_float3& y)
{
    return x.s[0] * y.s[0] + x.s[1] * y.s[1] + x.s[2] * y.s[2];
}
