#include <vector>

#include <CL/cl.hpp>

#include "image.hpp"

#include "../raytracer/sphere.h"
#include "../raytracer/raytracer.h"

using std::vector;

vector<float> createImage(
    const unsigned width,
    const unsigned height,
    const vector<Sphere>& spheres)
{
    vector<cl_float3> data(width * height);

    for (unsigned y = 0;  y < height;  y++)
    {
        for (unsigned x = 0;  x < width;  x++)
        {
            tracePixel(
                width,
                height,
                data.data(),
                spheres.data(),
                spheres.size(),
                y * width + x);
        }
    }

    vector<float> result(width * height * 3);
    for (unsigned x = 0; x < width; ++x)
    {
        for (unsigned y = 0; y < height; ++y)
        {
            for (unsigned c = 0; c < 3; ++c)
            {
                result[y * width * 3 + x * 3 + c] = data[y * width + x].s[c];
            }
        }
    }
    return result;
}
