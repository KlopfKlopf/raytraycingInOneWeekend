#include <math.h>
#include "ray.h"

// Check if the ray hits the sphere.
double hit_sphere(const Vec3 *center, double radius, const Ray *r) {
    Vec3 oc = vec3_subtract(center, &r->origin);
    double a = vec3_length_squared(&r->direction);
    double h = vec3_dot(&r->direction, &oc);
    double c = vec3_length_squared(&oc) - (radius * radius);
    double discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant)) / a;
    }
}
// Return the point on the ray at parameter t.
Vec3 ray_at(const Ray *r, double t) {
    Vec3 direction_t = vec3_scalar_multiply(t, &r->direction);
    return vec3_add(&r->origin, &direction_t);
}

// Calculate the ray color.
Color ray_color(const Ray *r) {
    Vec3 sphere_center = {0, 0, -1};
    double t = hit_sphere(&sphere_center, 0.5, r);
    if (t > 0.0) {
        Vec3 at_pos = ray_at(r, t);
        Vec3 normal_vector = vec3_subtract(&at_pos, &sphere_center);
        Vec3 N = vec3_unit_vector(&normal_vector);
        Color normal_color = {N.x + 1, N.y + 1, N.z + 1};
        return color_scalar_multiply(0.5, &normal_color);
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