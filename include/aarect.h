#ifndef AARECT_H
#define AARECT_H

#include "rtweekend.h"

#include "hittable.h"

class xy_rect : public hittable
{
public:
    xy_rect() {}
    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> mat);

    virtual bool hit(const ray &r, double t0, double t1, hit_record &rec) const override;
    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    double x0, x1, y0, y1, k;
    shared_ptr<material> mp;
};

class xz_rect : public hittable
{
public:
    xz_rect() {}

    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
            shared_ptr<material> mat);

    virtual bool hit(const ray &r, double t0, double t1, hit_record &rec) const override;

    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    double x0, x1, z0, z1, k;
    shared_ptr<material> mp;
};

class yz_rect : public hittable
{
public:
    yz_rect() {}

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,
            shared_ptr<material> mat);

    virtual bool hit(const ray &r, double t0, double t1, hit_record &rec) const override;

    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    double y0, y1, z0, z1, k;
    shared_ptr<material> mp;
};

#endif