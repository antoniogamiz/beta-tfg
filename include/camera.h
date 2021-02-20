#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera
{
public:
    void initialize(double aspect_ratio = 1.0);
    ray get_ray(double s, double t) const;

public:
    double vfov = 40;
    double aperture = 0;
    double focus_dist = 10;

    point3 lookfrom = point3(0, 0, -1);
    point3 lookat = point3(0, 1, 0);
    vec3 vup = vec3(0, 1, 0);

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};

#endif