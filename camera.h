#pragma once
#include <stdlib.h>
#include "rtweekend.h"
#include "vec3.h"
#include "hittables.h"
#include "color.h"
#include "ray.h"

typedef struct camera {
    double aspect_ratio;
    int image_width;
    int image_height;
    int samples_per_pixel;
    double pixel_samples_scale;
    Vec3 center;
    Vec3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
} Camera;

Camera* new_camera(double aspect_ratio, int image_width, int samples_per_pixel);
void initialize(Camera *cam);
void render(Camera *cam, const Hittables *world);
Color ray_color(const Ray *r, const Hittables *world);
Ray get_ray(const Camera *cam, int i, int j);
Vec3 sample_square(void);