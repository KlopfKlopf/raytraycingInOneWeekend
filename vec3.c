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
        if (-RT_INFINITY < lensq && lensq<= 1) {
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