#include <vector>

#include "image.hpp"

using std::vector;

vector<float> createImage(const unsigned width, const unsigned height)
{
    vector<float> image(width * height * 3);
    for (unsigned y = 0;  y < height;  y++)
    {
        for (unsigned x = 0;  x < width;  x++)
        {
            for (unsigned channel = 0; channel < 3; channel++)
            {
                image[y * width * 3 + x * 3 + channel] =
                    channel? (1.f * x * channel) / width : (1.f * y) / height;
            }
        }
    }
    return image;
}
