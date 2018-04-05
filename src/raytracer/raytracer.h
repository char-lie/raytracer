#ifndef __OPENCL_C_VERSION__

#include <CL/cl.hpp>

#define __global
#define __kernel

typedef cl_float3 float3;

#endif

#include "sphere.h"

__kernel void tracePixel(
    ulong width,
    ulong height,
    __global float3* output,
    __global const struct Sphere* spheres,
    ulong spheresCount,
    int index);

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef __kernel

#endif
