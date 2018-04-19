#ifndef __OPENCL_C_VERSION__

#include <CL/cl.hpp>

typedef cl_float3 float3;
typedef cl_float4 float4;

#endif

float sqr(float x)
{
    return x * x;
}

float4 float3ToFloat4(float3 x, float c)
{
    float4 result;
#ifndef __OPENCL_C_VERSION__
    result = x;
    result.s[3] = c;
#else
    result.xyz = x;
    result.w = c;
#endif
    return result;
}

float3 float4ToFloat3(float4 x)
{
#ifndef __OPENCL_C_VERSION__
    return x;
#else
    return x.xyz;
#endif
}

float getW(float4 x)
{
#ifndef __OPENCL_C_VERSION__
    return x.s[3];
#else
    return x.w;
#endif
}
