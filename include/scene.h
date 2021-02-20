#ifndef SCENE_H
#define SCENE_H

#include "rtweekend.h"

#include "camera.h"
#include "material.h"
#include "hittable_list.h"

#include <iostream>

class scene
{
public:
    void render();

    void print_ppm_header(int image_width, int image_height);
    color generate_pixel_color(int image_width, int image_height, int i, int j);
    color scale_color(color pixel_color, double scale_factor);

public:
    hittable_list world;
    camera cam;

    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 50;
    color background = color(0, 0, 0);

private:
    color ray_color(const ray &r, int depth);
};

#endif