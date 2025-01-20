#include "rtweekend.h"
#include "hittables.h"
#include "camera.h"

int main(void) {
    //World
    Hittables *world = init_hittables(10);
    Obj* sp1 = create_sphere(new_vec3(0, 0, -1), 0.5);
    Obj* sp2 = create_sphere(new_vec3(0, -100.5, -1), 100);

    hittables_add(world, sp1);
    hittables_add(world, sp2);

    Camera *cam = new_camera(16.0/9.0, 400, 100, 50);
    render(cam, world);

    hittables_clear(world);
    free(cam);
    return 0;
}