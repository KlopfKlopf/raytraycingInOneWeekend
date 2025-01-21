#pragma once
#include <math.h>
#include <stdlib.h>
#include "rtweekend.h"
#include "ray.h"
#include "interval.h"

typedef struct material Material;

typedef enum Object_kind {
    SPHERE
} Obj_kind;

typedef struct object{
    void* data;
    int refcount;
    Obj_kind kind;
} Obj;

typedef struct hittables {
    Obj **objects;
    size_t size;
    size_t capacity;
} Hittables;

typedef struct hit_record
{
    Vec3 point;
    Vec3 normal;
    Material *mat;
    double t;
    bool front_face;
} Hit_Record;

typedef struct sphere {
    Vec3 center;
    double radius;
    Material *material;
} Sphere;

bool object_hit(const Obj *obj, const Ray *r, Interval ray_t, Hit_Record *rec);
bool hittables_hit(const Hittables *hittables, const Ray *r, Interval ray_t, Hit_Record *rec);
void hit_record_set_face_normal(const Ray *r, const Vec3 *outward_normal, Hit_Record *rec);
Obj* new_object(void);
Obj* create_sphere(Vec3 postition, double radius, Material *mat);
void add_object_ref(Obj *obj);
void remove_object_ref(Obj *obj);
void free_object_data(Obj *obj);
Hittables* init_hittables(size_t capacity);
void hittables_add(Hittables *hittables, Obj *obj);
void hittables_remove(Hittables *hittables, Obj *obj);
void hittables_clear(Hittables *hittables);