#include "rtweekend.h"

#include "material.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "moving_sphere.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <future>

color ray_color(const ray &r, const hittable &world, int depth)
{
    hit_record rec;

    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

hittable_list random_scene()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, .5), 0);
                    world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

hittable_list two_spheres()
{
    hittable_list objects;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    objects.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
    objects.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    return objects;
}

hittable_list two_perlin_spheres()
{
    hittable_list objects;

    auto pertext = make_shared<noise_texture>(4);
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}

void generate_image_row(hittable_list world, camera cam, const int image_width, const int image_height, const int samples_per_pixel, const int min, const int max, std::vector<std::vector<std::vector<int>>> *image, const int max_depth)
{
    std::ofstream outfile;
    std::stringstream ss;
    ss << std::this_thread::get_id();
    std::string thread_id = ss.str();
    outfile.open("progress/" + thread_id);
    for (int j = max; j > min; --j)
    {
        std::vector<std::vector<int>> row_colors;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            row_colors.push_back(write_color_parallel(pixel_color, samples_per_pixel));
        }
        outfile << max - j << " "
                << " " << max - min << std::endl;
        (*image).push_back(row_colors);
    }
}

int main()
{
    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 25;
    const int max_depth = 25;

    // World
    hittable_list world;

    point3 lookfrom;
    point3 lookat;
    auto vfov = 40.0;
    auto aperture = 0.0;

    switch (0)
    {
    case 1:
        world = random_scene();
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vfov = 20.0;
        aperture = 0.1;
        break;
    case 2:
        world = two_spheres();
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vfov = 20.0;
        break;
    default:
    case 3:
        world = two_perlin_spheres();
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vfov = 20.0;
        break;
    }

    // Camera
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render

    const unsigned k = std::thread::hardware_concurrency();
    const int batch_size = floor(image_height / k);

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    // TODO: arreglar la asignacion de trabajo al ultimo thread, a no ser que sea multiplo, se quedan filas sin hacer
    std::vector<std::vector<std::vector<std::vector<int>>>> image_fragments(k, std::vector<std::vector<std::vector<int>>>());
    std::vector<std::thread> workers;
    for (unsigned n = 0; n < k; n++)
    {
        workers.push_back(std::thread(generate_image_row, world, cam, image_width, image_height, samples_per_pixel, image_height - 1 - (n + 1) * batch_size, image_height - 1 - n * batch_size, &image_fragments[n], max_depth));
    }

    for (unsigned n = 0; n < k; n++)
    {
        workers[n].join();
    }

    for (unsigned n = 0; n < k; n++)
    {
        for (unsigned i = 0; i < image_fragments[n].size(); i++)
        {
            for (unsigned j = 0; j < image_fragments[n][i].size(); j++)
            {
                std::vector<int> color = image_fragments[n][i][j];
                std::cout << color[0] << ' ' << color[1] << ' ' << color[2] << '\n';
            }
        }
    }
    std::cerr << "\nDone.\n";
}