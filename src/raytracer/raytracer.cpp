#include "sphere.h"

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
    int index)
{
    const int channels = 3;
    output[index] = (float3){0, 0, 0};
    float y = convert_float(index / width) / height;
    float x = convert_float(index % width) / width;
    // x *= x / y;
    output[index] = (float3){y, x / 2, x};
    float2 point = {x, y};
    global const struct Sphere* sphere;
    for (ulong i = 0; i < spheresCount; ++i)
    {
        sphere = &spheres[i];
        float3 start = {x, y, 0};
        float3 direction = {0, 0, 1};
        float dist = distanceRaySphere(sphere, start, direction);
        if (dist < INFINITY)
        {
            output[index] = sphere->color *
                fabs(dot(sphere->center, direction) - dist);
        }

    }
}

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global
#undef __kernel

#endif
