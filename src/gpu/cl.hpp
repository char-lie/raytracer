#include <string>
#include <vector>

#include <CL/cl.hpp>

using std::string;
using std::vector;
using cl::Program;

Program createProgram(const string& filename);
Program createProgram(const vector<string>& filenames);

const string clGetErrorString(int errorCode);
