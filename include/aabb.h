#ifndef AABB_H
#define AABB_H

#include "rtweekend.h"

class aabb
{
public:
    aabb() {}
    aabb(const point3 &a, const point3 &b);

    point3 min() const;
    point3 max() const;

    bool hit(const ray &r, double tmin, double tmax) const;

public:
    point3 _min;
    point3 _max;
};

aabb surrounding_box(aabb box0, aabb box1);

#endif