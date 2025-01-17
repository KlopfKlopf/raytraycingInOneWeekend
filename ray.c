#include "ray.h"

// Return the point on the ray at parameter t.
Vec3 ray_at(const Ray *r, double t) {
    Vec3 direction_t = vec3_scalar_multiply(t, &r->direction);
    return vec3_add(&r->origin, &direction_t);
}
