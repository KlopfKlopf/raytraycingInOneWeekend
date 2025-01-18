#include "rtweekend.h"
#include "hittables.h"
#include "camera.h"

int main(void) {
    //World
    Hittables *world = init_hittables(10);
    Vec3 pos_sp1 = {0, 0, -1};
    Vec3 pos_sp2 = {0, -100.5, -1};
    Obj* sp1 = create_object(SPHERE, &pos_sp1);
    Obj* sp2 = create_object(SPHERE, &pos_sp2);
    resize_object(sp1, 0.5, 0.0, 0.0);
    resize_object(sp2, 100.0, 0.0, 0.0);

    hittables_add(world, sp1);
    hittables_add(world, sp2);

    Camera *cam = new_camera(16.0/9.0, 400);
    render(cam, world);

    hittables_clear(world);
    free(cam);
    return 0;
}