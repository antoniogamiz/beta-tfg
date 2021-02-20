#ifndef SCENE_H
#define SCENE_H

#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "color.h"

#include <iostream>

class scene
{
public:
    void render()
    {
        const int image_height = static_cast<int>(image_width / aspect_ratio);

        cam.initialize(aspect_ratio);

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / (image_width - 1);
                    auto v = (j + random_double()) / (image_height - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, max_depth);
                }
                write_color_parallel(pixel_color, samples_per_pixel);
            }
        }

        std::cerr << "\nDone.\n";
    }

public:
    hittable_list world;
    camera cam;

    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 50;
    color background = color(0, 0, 0);

private:
    color ray_color(const ray &r, int depth)
    {
        hit_record rec;

        if (depth <= 0)
            return color(0, 0, 0);

        // If the ray hits nothing, return the background color.
        if (!world.hit(r, 0.001, infinity, rec))
            return background;

        ray scattered;
        color attenuation;
        color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return emitted;

        return emitted + attenuation * ray_color(scattered, depth - 1);
    }
};

#endif