#include "rtweekend.h"
#include "two_spheres.h"

int main()
{
    scene scene_desc;
    two_spheres(scene_desc);
    scene_desc.render();
}