#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define __CL_ENABLE_EXCEPTIONS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <CL/cl.hpp>

#include "cl.hpp"

#include "../raytracer/sphere.h"
#include "../raytracer/light.h"

using std::vector;
using std::cerr;
using std::endl;

using cl::Buffer;
using cl::Device;
using cl::CommandQueue;
using cl::Kernel;
using cl::Program;
using cl::Context;
using cl::NullRange;
using cl::NDRange;
using cl::Error;

vector<float> clImage(
    const unsigned width,
    const unsigned height,
    const vector<Sphere>& spheres,
    const vector<SpotLight>& lights)
{
    vector<cl_float3> data(width * height);

    Program program;
    vector<Device> devices;
    try
    {
        program = createProgram(vector<string>{
            "src/raytracer/raytracer.cpp",
            "src/raytracer/sphere.cpp",
            "src/raytracer/light.cpp",
            "kernels/raytracer.cl",
        });
        Context context{program.getInfo<CL_PROGRAM_CONTEXT>()};
        devices = vector<Device>{context.getInfo<CL_CONTEXT_DEVICES>()};
        Device& device = devices.front();

        Buffer outBuffer(
            context,
            CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
            sizeof(cl_float3) * data.size());
        Buffer spheresBuffer(
            context,
            CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
            sizeof(Sphere) * spheres.size(),
            const_cast<Sphere*>(spheres.data()));
        Buffer lightsBuffer(
            context,
            CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
            sizeof(SpotLight) * lights.size(),
            const_cast<SpotLight*>(lights.data()));

        Kernel kernel(program, "raytrace");
        unsigned arguments = 0;
        kernel.setArg(arguments++, outBuffer);
        kernel.setArg(arguments++, spheresBuffer);
        kernel.setArg(arguments++, static_cast<cl_ulong>(spheres.size()));
        kernel.setArg(arguments++, lightsBuffer);
        kernel.setArg(arguments++, static_cast<cl_ulong>(lights.size()));
        kernel.setArg(arguments++, static_cast<const cl_ulong>(width));
        kernel.setArg(arguments++, static_cast<const cl_ulong>(height));

        CommandQueue queue{context, device};

        queue.enqueueNDRangeKernel(kernel, NullRange, NDRange(data.size()));
        queue.enqueueReadBuffer(
            outBuffer, CL_FALSE, 0,
            sizeof(cl_float3) * data.size(), data.data());

        queue.finish();
    }
    catch (Error& e) {
        for (const Device& device : devices)
        {
            if (program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device)
             != CL_BUILD_ERROR)
            {
                continue;
            }

            cerr << "Build log for " << device.getInfo<CL_DEVICE_NAME>()
                 << ":" << endl
                 << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << endl;
        }
        cerr << "ERROR: " << e.what()
             << " (code " << e.err() << ", " << clGetErrorString(e.err()) << ")"
             << endl;
        throw;
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
