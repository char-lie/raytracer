#include "sphere.h"

__kernel void processArray(
    __global float3* output,
    __global struct Sphere* spheres,
    ulong spheresCount,
    ulong width,
    ulong height
)
{
    int index = get_global_id(0);
    const int channels = 3;
    output[index] = 0;
    float y = convert_float(index / width) / height;
    float x = convert_float(index % width) / width;
    // x *= x / y;
    output[index] = (float3)(y, x / 2, x);
    float2 point = {x, y};
    global struct Sphere* sphere;
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
