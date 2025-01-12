#include <stdbool.h>
#include "ray.h"

// Check if the ray hits the sphere.
bool hit_sphere(const Vec3 *center, double radius, const Ray *r) {
    Vec3 oc = vec3_subtract(center, &r->origin);
    double a = vec3_dot(&r->direction, &r->direction);
    double b = -2.0 * vec3_dot(&r->direction, &oc);
    double c = vec3_dot(&oc, &oc) - radius * radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
// Return the point on the ray at parameter t.
Vec3 ray_at(const Ray *r, double t) {
    Vec3 direction_t = vec3_scalar_multiply(t, &r->direction);
    return vec3_add(&r->origin, &direction_t);
}

// Calculate the ray color.
Color ray_color(const Ray *r) {
    Vec3 sphere_center = {0, 0, -1};
    if (hit_sphere(&sphere_center, 0.5, r)) {
        Color color = {1, 0, 0};
        return color;
    }
    Vec3 unit_direction = vec3_unit_vector(&r->direction);
    Color start_value = {1, 1, 1};
    Color end_value = {0.5, 0.7, 1};
    double a = 0.5 * (unit_direction.y + 1.0);

    Color blended_start_value = color_scalar_multiply((1.0-a), &start_value);
    Color blended_end_value = color_scalar_multiply(a, &end_value);
    Color blended_color = color_add(&blended_start_value, &blended_end_value);
    return blended_color;
}