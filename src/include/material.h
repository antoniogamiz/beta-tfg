#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class material
{
public:
    virtual bool scatter(
        const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material
{
public:
    lambertian(const color &a) : albedo(a) {}

    // TODO: we could just as well only scatter with some probability p and have attenuation
    // be albedo/p.
    virtual bool scatter(
        const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    color albedo;
};

// TODO: I do not see why dot(v,n) is there.
vec3 reflect(const vec3& v, const vec3 & n) {
    return v - 2 * dot(v, n)*n;
}

class metal : public material {
public:
    metal(const color& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return  (dot(scattered.direction(), rec.normal) > 0);
    }
public:
    color albedo;
};

#endif