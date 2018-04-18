#include "sphere.h"

#ifndef __OPENCL_C_VERSION__

#include <cmath>

#include "cpu.hpp"

#define __global
#define global

typedef cl_float3 float3;

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
    float far = - b + sqrt(D);
    float near = - b - sqrt(D);
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

global const struct Sphere* findNearestSphere(
    global const struct Sphere* spheres,
    ulong spheresCount,
    float3 rayStart,
    float3 rayDirection,
    float nearerThan,
    global const struct Sphere* ignoredSphere)
{
    global const struct Sphere* nearestSphere = NULL;

    global const struct Sphere* sphere;
    for (ulong i = 0; i < spheresCount; ++i)
    {
        sphere = &spheres[i];
        if (sphere == ignoredSphere)
        {
            continue;
        }
        float dist = distanceRaySphere(sphere, rayStart, rayDirection);
        if (dist < nearerThan)
        {
            nearestSphere = sphere;
            nearerThan = dist;
        }
    }
    return nearestSphere;
}

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global

#endif
