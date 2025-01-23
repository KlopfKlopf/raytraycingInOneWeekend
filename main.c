#include "rtweekend.h"
#include "hittables.h"
#include "camera.h"

int main(void) {
    //World
    Hittables *world = init_hittables(10);
    Obj* sphere_ground = create_sphere(new_vec3(0, -100.5, -1), 100, create_lambertian(new_color(0.8, 0.8, 0.0)));
    Obj* sphere_center = create_sphere(new_vec3(0, 0, -1.2), 0.5, create_lambertian(new_color(0.1, 0.2, 0.5)));
    Obj* sphere_left = create_sphere(new_vec3(-1.0, 0, -1.0), 0.5, create_dielectric(1.50));
    Obj* sphere_right = create_sphere(new_vec3(1.0, 0, -1.0), 0.5, create_metal(new_color(0.8, 0.6, 0.2), 1.0));

    hittables_add(world, sphere_ground);
    hittables_add(world, sphere_center);
    hittables_add(world, sphere_left);
    hittables_add(world, sphere_right);

    Camera *cam = new_camera(16.0/9.0, 400, 300, 50);
    render(cam, world);

    hittables_clear(world);
    free(cam);
    return 0;
}