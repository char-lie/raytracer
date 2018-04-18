#include "sphere.h"
#include "light.h"

#ifndef __OPENCL_C_VERSION__

#include <cmath>
#include <CL/cl.hpp>

#include "cpu.hpp"

#define __global
#define global
#define __kernel

typedef cl_float3 float3;
typedef cl_float2 float2;

#endif

__kernel void tracePixel(
    ulong width,
    ulong height,
    __global float3* output,
    const __global struct Sphere* spheres,
    ulong spheresCount,
    const __global struct SpotLight* lights,
    ulong lightsCount,
    int index)
{
    const int channels = 3;
    output[index] = (float3){0, 0, 0};
    float y = convert_float(index / width) / height;
    float x = convert_float(index % width) / width;
    // x *= x / y;
    output[index] = (float3){y, x / 2, x};

    float3 start = {x, y, 0};
    float3 direction = {0, 0, 1};

    global const struct Sphere* sphere = findNearestSphere(
        spheres,
        spheresCount,
        start,
        direction,
        INFINITY,
        NULL);
    if (sphere)
    {
        float dist = distanceRaySphere(sphere, start, direction);
        output[index] = sphere->color *
            fabs(dot(sphere->center, direction) - dist);
    }
}

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global
#undef __kernel

#endif
