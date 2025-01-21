#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "color.h"
#include "hittables.h"
#include "ray.h"

typedef enum material_kind {
    LAMBERTIAN,
    METAL,
} Material_Kind;

typedef struct material{
    void* data;
    int refcount;
    Material_Kind kind;
} Material;

typedef struct lambertian {
    Color albedo;
}Lambertian;

typedef struct metal {
    Color albedo;
}Metal;

Material* new_material(void);
Material* create_lambertian(const Color albedo);
Material* create_metal(const Color albedo);
void add_material_ref(Material *mat);
void remove_material_ref(Material *mat);
void free_material_data(Material *mat);
bool scatter(const Ray *r, const Hit_Record *rec, Color *attenuation, Ray *scattered);