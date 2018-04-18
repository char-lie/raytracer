#include <cmath>

#include <CL/cl.hpp>

#include "cpu.hpp"

cl_float3 operator*(const cl_float3& x, const float c)
{
    return {x.s[0] * c, x.s[1] * c, x.s[2] * c};
}

cl_float3 operator-(const cl_float3& x, float c)
{
    return {x.s[0] - c, x.s[1] - c, x.s[2] - c};
}

cl_float3 operator-(const cl_float3& x, const cl_float3& y)
{
    return {x.s[0] - y.s[0], x.s[1] - y.s[1], x.s[2] - y.s[2]};
}

float length(const cl_float3& x)
{
    return sqrt(dot(x, x));
}

float distance(const cl_float3& x, const cl_float3& y)
{
    return length(x - y);
}

float dot(const cl_float3& x, const cl_float3& y)
{
    return x.s[0] * y.s[0] + x.s[1] * y.s[1] + x.s[2] * y.s[2];
}
