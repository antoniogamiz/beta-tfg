#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"
#include "aabb.h"

class material;

class hit_record
{
public:
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    void set_face_normal(const ray &r, const vec3 &outward_normal);
};

class hittable
{
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
    virtual bool bounding_box(double t0, double t1, aabb &output_box) const = 0;
};

class translate : public hittable
{
public:
    translate(shared_ptr<hittable> p, const vec3 &displacement);
    virtual bool hit(
        const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    shared_ptr<hittable> ptr;
    vec3 offset;
};

class rotate_y : public hittable
{
public:
    rotate_y(shared_ptr<hittable> p, double angle);

    virtual bool hit(
        const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    shared_ptr<hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    aabb bbox;
};

#endif