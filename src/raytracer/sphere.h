#ifndef SPHERE_H
#define SPHERE_H


#ifndef __OPENCL_C_VERSION__

#include <cmath>
#include <CL/cl.hpp>
typedef cl_float3 float3;

#define __global
#define global

#endif // __OPENCL_C_VERSION__

struct Sphere
{
    float radius;
    float3 center;
    float3 color;
};

float distanceRaySphere(
    __global const struct Sphere* sphere,
    float3 start,
    float3 direction);
global const struct Sphere* findNearestSphere(
    global const struct Sphere* spheres,
    ulong spheresCount,
    float3 rayStart,
    float3 rayDirection,
    float nearerThan,
    global const struct Sphere* ignoredSphere);

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global

#endif // __OPENCL_C_VERSION__

#endif // SPHERE_H
