#include "sphere.h"
#include "light.h"

#ifndef __OPENCL_C_VERSION__

#include <CL/cl.hpp>

#define __global
#define __kernel

typedef cl_float3 float3;
typedef cl_float4 float4;

#endif

__kernel void tracePixel(
    ulong width,
    ulong height,
    __global float3* output,
    __global const struct Sphere* spheres,
    ulong spheresCount,
    __global const struct SpotLight* lights,
    ulong lightsCount,
    int index);

float4 rayTrace(
    __global const struct Sphere* spheres,
    ulong spheresCount,
    __global const struct SpotLight* lights,
    ulong lightsCount,
    float3 start,
    float3 direction);

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef __kernel

#endif
