#pragma once
#include <math.h>
#include "rtweekend.h"
#include "ray.h"

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
    double t;
    bool front_face;
} Hit_Record;

typedef struct sphere {
    Vec3 center;
    double radius;
} Sphere;

bool object_hit(const Obj *obj, const Ray *r, double ray_tmin, double ray_tmax, Hit_Record *rec);
bool hittables_hit(const Hittables *hittables, const Ray *r, double ray_tmin, double ray_tmax, Hit_Record *rec);
void hit_record_set_face_normal(const Ray *r, const Vec3 *outward_normal, Hit_Record *rec);
Obj* create_object(Obj_kind kind, Vec3 *position);
void resize_object(Obj *obj, double s1, double s2, double s3);
void add_object_ref(Obj *obj);
void remove_object_ref(Obj *obj);
void free_object_data(Obj *obj);
Hittables* init_hittables(size_t capacity);
void hittables_add(Hittables *hittables, Obj *obj);
void hittables_remove(Hittables *hittables, Obj *obj);
void hittables_clear(Hittables *hittables);