#pragma once
#include "rtweekend.h"
#include "vec3.h"
#include "color.h"

typedef struct ray {
    Vec3 origin;
    Vec3 direction;
} Ray;

double hit_sphere(const Vec3 *center, double radius, const Ray *r);
Vec3 ray_at(const Ray *r, double t);
