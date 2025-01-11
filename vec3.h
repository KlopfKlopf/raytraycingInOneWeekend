#pragma once

typedef struct vec3 {
    double x;
    double y;
    double z;
} Vec3;

Vec3 vec3_negate(const Vec3 *v);
Vec3 vec3_add(const Vec3 *v1, const Vec3 *v2);
Vec3 vec3_subtract(const Vec3 *v1, const Vec3 *v2);
Vec3 vec3_scalar_divide(double s, const Vec3 *v);
Vec3 vec3_scalar_multiply(double s, const Vec3 *v);
Vec3 vec3_vector_multiply(const Vec3 *v1, const Vec3 *v2);
Vec3 vec3_cross(const Vec3 *v1, const Vec3 *v2);
Vec3 vec3_unit_vector(const Vec3 *v);
double vec3_dot(const Vec3 *v1, const Vec3 *v2);
double vec3_length(const Vec3 *v);
double vec3_length_squared(const Vec3 *v);