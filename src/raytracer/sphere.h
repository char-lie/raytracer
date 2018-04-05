#ifndef SPHERE_H
#define SPHERE_H


#ifndef __OPENCL_C_VERSION__

#define __global

#include <CL/cl.hpp>
typedef cl_float3 float3;

#endif // __OPENCL_C_VERSION__

struct Sphere
{
    float radius;
    float3 center;
    float3 color;
};

float distanceRaySphere(__global const struct Sphere* sphere, float3 start, float3 direction);
float sqr(float x);

#ifndef __OPENCL_C_VERSION__

#undef __global

#endif // __OPENCL_C_VERSION__

#endif // SPHERE_H
