#ifndef SPHERE_H
#define SPHERE_H


#ifndef __OPENCL_C_VERSION__

#define __global

#include <CL/cl.hpp>
#define float3 cl_float3

#endif // __OPENCL_C_VERSION__

struct Sphere
{
    float radius;
    float3 center;
    float3 color;
};

#ifndef __OPENCL_C_VERSION__

#include <glm/vec3.hpp>
using glm::vec3;
#undef float3
#define float3 vec3

#endif // __OPENCL_C_VERSION__

float distanceRaySphere(__global struct Sphere* sphere, float3 start, float3 direction);
float sqr(float x);

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef float3

#endif // __OPENCL_C_VERSION__

#endif // SPHERE_H
