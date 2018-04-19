#ifndef __OPENCL_C_VERSION__

#include <CL/cl.hpp>

typedef cl_float3 float3;
typedef cl_float4 float4;

#endif

float sqr(float x);
float4 float3ToFloat4(float3 x, float c);
float3 float4ToFloat3(float4 x);
float getW(float4 x);
