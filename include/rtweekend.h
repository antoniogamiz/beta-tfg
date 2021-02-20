#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <random>
#include <cstdlib>
#include <limits>
#include <memory>
#include <iostream>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

// inline double random_double()
// {
//     static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return distribution(generator);
// }

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max));
}

// Common Headers

#include "ray.h"
#include "vec3.h"

void write_color(std::ostream &out, color pixel_color)
{
    out
        << static_cast<int>(255.999 * clamp(pixel_color.x(), 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(pixel_color.y(), 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(pixel_color.z(), 0.0, 0.999)) << '\n';
}

std::vector<int> write_color_parallel(color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    std::vector<int> rgb = {static_cast<int>(255.999 * clamp(r, 0.0, 0.999)),
                            static_cast<int>(255.999 * clamp(g, 0.0, 0.999)),
                            static_cast<int>(255.999 * clamp(b, 0.0, 0.999))};

    return rgb;
}

#endif