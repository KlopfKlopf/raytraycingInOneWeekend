#include "vec3.h"
#include "color.h"

typedef struct ray {
    Vec3 origin;
    Vec3 direction;
} Ray;

Vec3 ray_at(const Ray *r, double t);
Color ray_color(const Ray *r);