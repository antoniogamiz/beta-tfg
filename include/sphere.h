#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m);

    virtual bool hit(const ray &r, double tmin, double tmax, hit_record &rec) const override;
    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

#endif