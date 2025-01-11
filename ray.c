#include "ray.h"
#include <stdio.h>

Vec3 ray_at(const Ray *r, double t) {
    Vec3 direction_t = vec3_scalar_multiply(t, &r->direction);
    return vec3_add(&r->origin, &direction_t);
}

Color ray_color(const Ray *r) {
    Vec3 unit_direction = vec3_unit_vector(&r->direction);
    Color start_value = {1, 1, 1};
    Color end_value = {0.5, 0.7, 1};
    double a = 0.5 * ((r->direction.y) + 1.0);

    Color blended_start_value = color_scalar_multiply((1.0-a), &start_value);
    Color blended_end_value = color_scalar_multiply(a, &end_value);
    Color blended_color = color_add(&blended_start_value, &blended_end_value);

    printf("blended_color: (%f, %f, %f)\n", blended_color.r, blended_color.g, blended_color.b);
    return blended_color;
}