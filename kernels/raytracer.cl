#include "sphere.h"
#include "raytracer.h"

__kernel void raytrace(
    __global float3* output,
    __global struct Sphere* spheres,
    ulong spheresCount,
    __global struct SpotLight* lights,
    ulong lightsCount,
    ulong width,
    ulong height
)
{
    tracePixel(
        width,
        height,
        output,
        spheres,
        spheresCount,
        lights,
        lightsCount,
        get_global_id(0));
}
