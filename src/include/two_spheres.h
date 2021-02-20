#ifndef TWO_SPHERES_H
#define TWO_SPHERES_H

#include "scene.h"
#include "material.h"
#include "color.h"
#include "sphere.h"

void two_spheres(scene &scene_desc)
{
    scene_desc.image_width = 300;
    scene_desc.aspect_ratio = 16.0 / 9.0;
    scene_desc.samples_per_pixel = 5;
    scene_desc.max_depth = 5;
    scene_desc.background = color(0.70, 0.80, 1.00);

    scene_desc.cam.lookfrom = point3(13, 2, 3);
    scene_desc.cam.lookat = point3(0, 0, 0);
    scene_desc.cam.vfov = 20.0;
    scene_desc.cam.aperture = 0.0;

    hittable_list &world = scene_desc.world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));
}

#endif
