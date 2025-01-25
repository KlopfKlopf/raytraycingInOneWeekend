#include "vec3.h"

Vec3 new_vec3(double x, double y, double z) {
    Vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

// Negate the Vector and return the resulting Vector.
Vec3 vec3_negate(const Vec3 *v) {
    Vec3 result;
    result.x = -v->x;
    result.y = -v->y;
    result.z = -v->z;
    return result;
}

// Add 2 Vectors and return the resulting Vector.
Vec3 vec3_add(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->x + v2->x;
    result.y = v1->y + v2->y;
    result.z = v1->z + v2->z;
    return result;
}

// Subtract 2 Vectors and return the resulting Vector.
Vec3 vec3_subtract(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->x - v2->x;
    result.y = v1->y - v2->y;
    result.z = v1->z - v2->z;
    return result;
}

// Scale the Vector down and return the resulting Vector.
Vec3 vec3_scalar_divide(double s, const Vec3 *v) {
    Vec3 result;
    result.x = v->x / s;
    result.y = v->y / s;
    result.z = v->z / s;
    return result;
}

// Scale the Vector up by x and return the resulting Vector.
Vec3 vec3_scalar_multiply(double s, const Vec3 *v) {
    Vec3 result;
    result.x = v->x * s;
    result.y = v->y * s;
    result.z = v->z * s;
    return result;
}

// Multiply 2 Vectors and return the resulting Vector
Vec3 vec3_vector_multiply(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->x * v2->x;
    result.y = v1->y * v2->y;
    result.z = v1->z * v2->z;
    return result;
}

// Calculate the Cross Product of the given Vectors and return the resulting Vector.
Vec3 vec3_cross(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->y * v2->z - v1->z * v2->y;
    result.y = v1->z * v2->x - v1->x * v2 ->z;
    result.z = v1->x * v2->y - v1->y * v2->x;
    return result;
}

// Normalize the Vector
Vec3 vec3_unit_vector(const Vec3 *v) {
    Vec3 result;
    double len = vec3_length(v);
    result.x = v->x / len;
    result.y = v->y / len;
    result.z = v->z / len;
    return result;
}

Vec3 vec3_random_unit_vector(void) {
    while (true) {
        Vec3 p = vec3_random_range(-1, 1);
        double lensq = vec3_length_squared(&p);
        if (1e-160 < lensq && lensq<= 1) {
            return vec3_scalar_divide(sqrt(lensq), &p);
        }
    }
}

Vec3 vec3_random_on_hemisphere(const Vec3 *normal) {
    Vec3 on_unit_sphere = vec3_random_unit_vector();
    if(vec3_dot(&on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    } else {
        return vec3_negate(&on_unit_sphere);
    }
}

Vec3 vec3_reflect(const Vec3 *v, const Vec3 *n) {
    double dot_result = vec3_dot(v, n);
    Vec3 scaled_unit_vector = vec3_scalar_multiply(dot_result, n);
    Vec3 outward_scaled_unit_vec = vec3_scalar_multiply(2, &scaled_unit_vector);
    return vec3_subtract(v, &outward_scaled_unit_vec);
}

Vec3 vec3_refract(const Vec3 *uv, const Vec3 *n, double etai_over_etat) {
    Vec3 negative_uv = vec3_negate(uv);
    double cos_theta = fmin(vec3_dot(&negative_uv, n), 1.0);
    Vec3 refracted_normal = vec3_scalar_multiply(cos_theta, n);
    Vec3 refracted_vec = vec3_add(uv, &refracted_normal);
    Vec3 r_out_perp = vec3_scalar_multiply(etai_over_etat, &refracted_vec);
    double discriminant = fabs((1.0 - vec3_length_squared(&r_out_perp)));
    double parallel_magnitude = sqrt(discriminant);
    Vec3 r_out_parallel = vec3_scalar_multiply(-parallel_magnitude, n);
    Vec3 refracted = vec3_add(&r_out_perp, &r_out_parallel);
    return refracted;
}

Vec3 vec3_random(void) {
    return new_vec3(random_double(), random_double(), random_double());
}

Vec3 vec3_random_range(double min, double max) {
    return new_vec3(random_double_range(min, max), random_double_range(min, max), random_double_range(min, max));
}

// Calculate the length of the Vector.
double vec3_length(const Vec3 *v) {
    return sqrt(vec3_length_squared(v));
}

// Helper Function to calculate the Vector length.
double vec3_length_squared(const Vec3 *v) {
    return (v->x * v->x + v->y * v->y + v->z * v->z);
}

// Calculate the Dot product of the given Vectors.
double vec3_dot(const Vec3 *v1, const Vec3 *v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

bool vec3_near_zero(const Vec3 *v) {
    double s = 1e-8;
    return (fabs(v->x) < s) && (fabs(v->y) < s) && (fabs(v->z) < s);
}