#ifndef HITTABLE_LIST_H
#define HITTABL_LIST_H

#include "rtweekend.h"

#include "aabb.h"
#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object);

    void clear();
    void add(shared_ptr<hittable> object);

    virtual bool hit(const ray &r, double tmin, double tmax, hit_record &rec) const override;
    virtual bool bounding_box(double t0, double t1, aabb &output_box) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

#endif