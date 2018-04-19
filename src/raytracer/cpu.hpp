#include <CL/cl.hpp>

cl_float4 operator-(const cl_float4& x, const cl_float4& y);
cl_float4 operator+(const cl_float4& x, const cl_float4& y);
cl_float4 operator-(const cl_float4& x, float c);
cl_float4 operator*(const cl_float4& x, const float c);
cl_float4 operator/(const cl_float4& x, const float c);
cl_float4& operator/=(cl_float4& x, const float c);
cl_float4& operator+=(cl_float4& x, const cl_float4& y);
float length(const cl_float4& x);
float distance(const cl_float4& x, const cl_float4& y);
float dot(const cl_float4& x, const cl_float4& y);
float min(float x, float y);
float max(float x, float y);

#define convert_float(x) static_cast<float>(x)
