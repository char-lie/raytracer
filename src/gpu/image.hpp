#include <vector>

#include "../raytracer/sphere.h"

using std::vector;

vector<float> clImage(
    const unsigned width,
    const unsigned height,
    const vector<Sphere>& spheres);
