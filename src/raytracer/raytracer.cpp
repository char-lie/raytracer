#include "common.h"
#include "raytracer.h"
#include "sphere.h"
#include "light.h"

#ifndef __OPENCL_C_VERSION__

#include <cmath>
#include <CL/cl.hpp>

#include "cpu.hpp"

#define __global
#define global
#define __kernel

typedef cl_float2 float2;
typedef cl_float3 float3;
typedef cl_float4 float4;

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
    float pixelWidth = 1.f / width;
    float pixelHeight = 1.f / height;
    // x *= x / y;
    output[index] = (float3){y, x / 2, x};

    float4 fullColor = (float4){0, 0, 0, 0};
    const int FSAA_FACTOR = 2;
    for (int step = 0; step < FSAA_FACTOR * FSAA_FACTOR; ++step)
    {
        int i = step / FSAA_FACTOR;
        int j = step % FSAA_FACTOR;
        float dx = (pixelWidth / FSAA_FACTOR) * (i - FSAA_FACTOR / 2);
        float dy = (pixelHeight / FSAA_FACTOR) * (j - FSAA_FACTOR / 2);
        float3 start = {x + dx, y + dy, 0};
        float3 direction = {0, 0, 1};
        fullColor += rayTrace(
            spheres,
            spheresCount,
            lights,
            lightsCount,
            start,
            direction);
    }
    // fullColor /= convert_float(FSAA_FACTOR * FSAA_FACTOR);
    fullColor = fullColor / convert_float(FSAA_FACTOR * FSAA_FACTOR);
    float alpha = getW(fullColor);
    float3 baseColor = float4ToFloat3(fullColor) * alpha;
    output[index] = output[index] * (1 - alpha) + baseColor;
}

float4 rayTrace(
    __global const struct Sphere* spheres,
    ulong spheresCount,
    __global const struct SpotLight* lights,
    ulong lightsCount,
    float3 start,
    float3 direction)
{
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
        float3 color =
            sphere->color *
            calculateBrightness(
                start + direction * dist,
                lights,
                lightsCount,
                spheres,
                spheresCount,
                sphere);
        return float3ToFloat4(color, 1);
    }
    return (float4){0, 0, 0, 0};
}

#ifndef __OPENCL_C_VERSION__

#undef __global
#undef global
#undef __kernel

#endif
