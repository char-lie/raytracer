#ifndef LIGHT_H
#define LIGHT_H


#ifndef __OPENCL_C_VERSION__

#include <CL/cl.hpp>
typedef cl_float3 float3;

#define __global
#define global

#endif // __OPENCL_C_VERSION__

struct SpotLight
{
    float3 position;
    float intensity;
};

bool isLit(
    float3 point,
    struct SpotLight light,
    global const struct Sphere* spheres,
    ulong spheresCount,
    global const struct Sphere* currentSphere);

float calculateBrightness(
    float3 point,
    global const struct SpotLight* lights,
    ulong lightsCount,
    global const struct Sphere* spheres,
    ulong spheresCount,
    global const struct Sphere* currentSphere);

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global

#endif // __OPENCL_C_VERSION__

#endif // LIGHT_H
