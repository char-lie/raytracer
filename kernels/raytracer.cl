#include "sphere.h"
#include "raytracer.h"

__kernel void raytrace(
    __global float3* output,
    __global struct Sphere* spheres,
    ulong spheresCount,
    ulong width,
    ulong height
)
{
    tracePixel(width, height, output, spheres, spheresCount, get_global_id(0));
}
