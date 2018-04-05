#include "sphere.h"

#ifndef __OPENCL_C_VERSION__

#include <glm/geometric.hpp>

#include "cpu.hpp"

#ifdef __global
#define GLOBAL_DEFINED
#else
#define __global
#endif

typedef cl_float3 float3;

using glm::dot;

#endif

float sqr(float x)
{
    return x * x;
}

float distanceRaySphere(
    __global const struct Sphere* sphere,
    float3 start,
    float3 direction)
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

#ifdef GLOBAL_DEFINED
#undef __global
#endif

#endif
