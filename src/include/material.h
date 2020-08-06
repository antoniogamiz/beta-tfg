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
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return  (dot(scattered.direction(), rec.normal) > 0);
    }
public:
    color albedo;
    double fuzz;
};

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_perp = etai_over_etat * (uv+cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0-r_out_perp.length_squared()))*n;
    return r_out_perp + r_out_parallel;
}

class dielectric : public material {
public:
    dielectric(double ri) : ref_idx(ri) {}
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color & attenuation, ray &scattered
    ) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double etai_over_etat = rec.front_face ? (1.0/ref_idx) : ref_idx;

        vec3 unit_direction = unit_vector(r_in.direction());
        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }
public:
    double ref_idx;
};

#endif