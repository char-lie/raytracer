#include "sphere.h"
#include "light.h"

#ifndef __OPENCL_C_VERSION__

#include <cmath>
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)

#include "cpu.hpp"

#define __global
#define global

typedef cl_float3 float3;

#endif

bool isLit(
    float3 point,
    struct SpotLight light,
    global const struct Sphere* spheres,
    ulong spheresCount,
    global const struct Sphere* currentSphere)
{
    float3 direction = (light.position - point);
    float dist = length(direction);
    direction /= dist;
    return NULL == findNearestSphere(
        spheres,
        spheresCount,
        point,
        direction,
        dist,
        currentSphere);
}

float calculateBrightness(
    float3 point,
    global const struct SpotLight* lights,
    ulong lightsCount,
    global const struct Sphere* spheres,
    ulong spheresCount,
    global const struct Sphere* currentSphere)
{
    float brightness = 0.f;
    for (ulong i = 0; i < lightsCount; ++i)
    {
        if (isLit(point, lights[i], spheres, spheresCount, currentSphere))
        {
            float3 normal = point - currentSphere->center;
            float3 lightRay = lights[i].position - point;
            float multiplier = dot(
                normal / length(normal),
                lightRay / length(lightRay));
            brightness += lights[i].intensity * max(multiplier, 0.f);
        }
    }
    return min(brightness, 1.f);
}

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global

#endif
