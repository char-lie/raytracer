#include "sphere.h"

#ifndef __OPENCL_C_VERSION__

#define __global

#include <cmath>
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

using glm::vec3;
using glm::dot;
using std::min;

#include <CL/cl.hpp>
// #define float3 cl_float3
#define float3 vec3

float3 operator-(const vec3& x, const cl_float3& y)
{
    return float3{x.x - y.s[0], x.y - y.s[1], x.z - y.s[2]};
}

float norm(const vec3& x)
{
    return x.x * x.x + x.y * x.y + x.z * x.z;
}

float distance(const vec3& x, const cl_float3& y)
{
    return norm(x - y);
}

#endif

float sqr(float x)
{
    return x * x;
}

float distanceRaySphere(__global struct Sphere* sphere, float3 start, float3 direction)
{
    float D =
        sqr(dot(direction, start - sphere->center)) -
        sqr(distance(start, sphere->center)) +
        sqr(sphere->radius);
    if (D < 0)
    {
        return INFINITY;
    }
    float b = dot(direction, start - sphere->center);
    float near = - b + sqrt(D);
    float far = - b - sqrt(D);
    if (far < 0)
    {
        return INFINITY;
    }
    else if (near < 0)
    {
        return far;
    }
    else
    {
        return near;
    }
}

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef float3

#endif
