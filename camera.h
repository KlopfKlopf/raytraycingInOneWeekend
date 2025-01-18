#pragma once
#include "vec3.h"
#include "hittables.h"
#include "color.h"
#include "ray.h"

typedef struct camera {
    double aspect_ratio;
    int image_width;
    int image_height;
    Vec3 center;
    Vec3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
} Camera;

Camera* new_camera(double aspect_ratio, int image_width);
void initialize(Camera *cam);
void render(Camera *cam, const Hittables *world);
Color ray_color(const Ray *r, const Hittables *world);