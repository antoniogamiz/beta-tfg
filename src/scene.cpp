#include "scene.h"

void scene::render()
{
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    cam.initialize(aspect_ratio);

    print_ppm_header(image_width, image_height);
    for (int j = image_height - 1; j >= 0; --j)
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color = generate_pixel_color(image_width, image_height, i, j);
            write_color(std::cout, pixel_color);
        }
}

void scene::print_ppm_header(int image_width, int image_height)
{
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
}

color scene::generate_pixel_color(int image_width, int image_height, int i, int j)
{
    color pixel_color(0, 0, 0);
    for (int s = 0; s < samples_per_pixel; ++s)
    {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, max_depth);
    }

    return scale_color(pixel_color, 1.0 / samples_per_pixel);
}

color scene::scale_color(color pixel_color, double scale_factor)
{
    auto r = sqrt(scale_factor * pixel_color.x());
    auto g = sqrt(scale_factor * pixel_color.y());
    auto b = sqrt(scale_factor * pixel_color.z());
    color scaled_color(r, g, b);
    return scaled_color;
}

color scene::ray_color(const ray &r, int depth)
{
    hit_record rec;

    if (depth <= 0)
        return color(0, 0, 0);

    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted +
           attenuation * ray_color(scattered, depth - 1);
}