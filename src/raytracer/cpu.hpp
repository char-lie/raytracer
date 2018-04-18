#include <CL/cl.hpp>

cl_float3 operator-(const cl_float3& x, const cl_float3& y);
cl_float3 operator+(const cl_float3& x, const cl_float3& y);
cl_float3 operator-(const cl_float3& x, float c);
cl_float3 operator*(const cl_float3& x, const float c);
cl_float3 operator/(const cl_float3& x, const float c);
cl_float3& operator/=(cl_float3& x, const float c);
float length(const cl_float3& x);
float distance(const cl_float3& x, const cl_float3& y);
float dot(const cl_float3& x, const cl_float3& y);

#define convert_float(x) static_cast<float>(x)
