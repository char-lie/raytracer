#include <CL/cl.hpp>
#include <glm/vec3.hpp>

using glm::vec3;

vec3 operator-(const vec3& x, const cl_float3& y);
vec3 operator-(const cl_float3& x, const cl_float3& y);
vec3 operator-(const cl_float3& x, float c);
float3 operator*(const cl_float3& x, const float c);
float norm(const vec3& x);
float distance(const cl_float3& x, const cl_float3& y);
float dot(const cl_float3& x, const vec3& y);
float dot(const cl_float3& x, const cl_float3& y);

#define convert_float(x) static_cast<float>(x)
