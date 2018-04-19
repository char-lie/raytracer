#include <cmath>

#include <CL/cl.hpp>

#include "cpu.hpp"

cl_float4 operator*(const cl_float4& x, const float c)
{
    return
        {x.s[0] * c, x.s[1] * c, x.s[2] * c, x.s[3] / c};
}

cl_float4 operator/(const cl_float4& x, const float c)
{
    return
        {x.s[0] / c, x.s[1] / c, x.s[2] / c, x.s[3] / c};
}

cl_float4& operator/=(cl_float4& x, const float c)
{
    x.s[0] /= c;
    x.s[1] /= c;
    x.s[2] /= c;
    x.s[3] /= c;
    return x;
}

cl_float4 operator-(const cl_float4& x, float c)
{
    return
        {x.s[0] - c, x.s[1] - c, x.s[2] - c};
}

cl_float4 operator-(const cl_float4& x, const cl_float4& y)
{
    return
        {x.s[0] - y.s[0], x.s[1] - y.s[1], x.s[2] - y.s[2], x.s[3] - y.s[3]};
}

cl_float4 operator+(const cl_float4& x, const cl_float4& y)
{
    return
        {x.s[0] + y.s[0], x.s[1] + y.s[1], x.s[2] + y.s[2], x.s[3] + y.s[3]};
}

cl_float4& operator+=(cl_float4& x, const cl_float4& y)
{
    x.s[0] += y.s[0];
    x.s[1] += y.s[1];
    x.s[2] += y.s[2];
    x.s[3] += y.s[3];
    return x;
}

float length(const cl_float4& x)
{
    return sqrt(dot(x, x));
}

float distance(const cl_float4& x, const cl_float4& y)
{
    return length(x - y);
}

float dot(const cl_float4& x, const cl_float4& y)
{
    return
        x.s[0] * y.s[0] + x.s[1] * y.s[1] + x.s[2] * y.s[2];
}

float min(float x, float y) {
    return x < y ? x : y;
}

float max(float x, float y) {
    return x > y ? x : y;
}
