#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

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