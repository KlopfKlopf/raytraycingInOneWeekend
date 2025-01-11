#include <math.h>

#include "vec3.h"

Vec3 vec3_negate(const Vec3 *v) {
    Vec3 result;
    result.x = -v->x;
    result.y = -v->y;
    result.z = -v->z;
    return result;
}

Vec3 vec3_add(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->x + v2->x;
    result.y = v1->y + v2->y;
    result.z = v1->z + v2->z;
    return result;
}

Vec3 vec3_subtract(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->x - v2->x;
    result.y = v1->y - v2->y;
    result.z = v1->z - v2->z;
    return result;
}

Vec3 vec3_scalar_divide(double s, const Vec3 *v) {
    Vec3 result;
    result.x = v->x / s;
    result.y = v->y / s;
    result.z = v->z / s;
    return result;
}

Vec3 vec3_scalar_multiply(double s, const Vec3 *v) {
    Vec3 result;
    result.x = v->x * s;
    result.y = v->y * s;
    result.z = v->z * s;
    return result;
}

Vec3 vec3_vector_multiply(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->x * v2->x;
    result.y = v1->y * v2->y;
    result.z = v1->z * v2->z;
    return result;
}

Vec3 vec3_cross(const Vec3 *v1, const Vec3 *v2) {
    Vec3 result;
    result.x = v1->y * v2->z - v1->z * v2->y;
    result.y = v1->z * v2->x - v1->x * v2 ->z;
    result.z = v1->x * v2->y - v1->y * v2->x;
    return result;
}

Vec3 vec3_unit_vector(const Vec3 *v) {
    Vec3 result;
    double len = vec3_length(v);
    result.x = v->x / len;
    result.y = v->y / len;
    result.z = v->z / len;
    return result;
}


double vec3_length(const Vec3 *v) {
    return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(const Vec3 *v) {
    return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double vec3_dot(const Vec3 *v1, const Vec3 *v2) {
    return v1->x * v2->x + v1->y + v2->y + v1->z + v2->z;
}