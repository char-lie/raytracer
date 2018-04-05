#include <vector>

#include "../raytracer/sphere.h"

using std::vector;

vector<float> createImage(
    const unsigned width,
    const unsigned height,
    const vector<Sphere>& spheres);
