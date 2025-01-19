#include "hittables.h"

// Create Objects of different types at posititons with default size

Obj* new_object(void) {
    Obj* obj;
    obj = malloc(sizeof(Obj));
    if (obj == NULL) {
        exit(1);
    }
    obj->refcount = 0;
    return obj;
}

Obj* create_sphere(Vec3 position, double radius) {
    Obj *obj = new_object();
    obj->kind = SPHERE;
    Sphere *sphere = malloc(sizeof(Sphere));
    if (sphere == NULL) {
        free(obj);
        exit(1);
    }
    sphere->center = position;
    sphere->radius = radius;
    obj->data = sphere;
    add_object_ref(obj);
    return obj;
}

void add_object_ref(Obj *obj) {
    if(obj == NULL) {
        return;
    }
    obj->refcount++;
}

void remove_object_ref(Obj *obj) {
    if (obj == NULL) {
        return;
    }
    obj->refcount--;
    if(obj->refcount == 0) {
        free_object_data(obj);
        free(obj);
    }
}

void free_object_data(Obj *obj) {
        if (obj->data == NULL) {
            return;
        }
        free(obj->data);
}

Hittables* init_hittables(size_t capacity) {
    Hittables *hittables = malloc(sizeof(Hittables));
    if (hittables == NULL) {
        exit(1);
    }

    hittables->objects = malloc(sizeof(Obj*) * capacity);
    if (hittables->objects == NULL) {
        free(hittables);
        exit(1);
    }
    hittables->capacity = capacity;
    hittables->size = 0;

    return hittables;
}

void hittables_add(Hittables *hittables, Obj *obj) {
    if (hittables == NULL || obj == NULL) {
        return;
    }
    if (hittables->size == hittables->capacity) {
        hittables->capacity *= 2;
        hittables->objects = realloc(hittables->objects, sizeof(Obj*) *  hittables->capacity);

        if (hittables->objects == NULL) {
            for (size_t i = 0; i < hittables->size; i++) {
                remove_object_ref(hittables->objects[i]);
            }
            free(hittables->objects);
            free(hittables);
            exit(1);
        }
    }
    hittables->objects[hittables->size] = obj;
    hittables->size++;
}

void hittables_remove(Hittables *hittables, Obj *obj) {
    if (hittables == NULL || obj ==  NULL) {
        return;
    }

    size_t i;
    for (i = 0; i < hittables->size; i++) {
        if (hittables->objects[i] == obj) {
            break;
        }
    }

    if (i == hittables->size) {
        return;
    }

    remove_object_ref(hittables->objects[i]);

    for (size_t j = i; j < hittables->size - 1; ++j) {
        hittables->objects[j] = hittables->objects[j+1];
    }
    hittables->size--;
    hittables->objects[hittables->size] = NULL;
}

void hittables_clear(Hittables *hittables) {
    if (hittables == NULL) {
        return;
    }
    for (size_t i = 0; i < hittables->size; i++) {
        remove_object_ref(hittables->objects[i]);
    }
    free(hittables->objects);
    free(hittables);
}

bool hittables_hit(const Hittables *hittables, const Ray *r, Interval ray_t, Hit_Record *rec) {
    Hit_Record temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (size_t i = 0; i<hittables->size; i++) {
        Interval interval = {ray_t.min, closest_so_far};
        if (object_hit(hittables->objects[i], r, interval, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

bool object_hit(const Obj *obj, const Ray *r, Interval ray_t, Hit_Record *rec) {
    switch (obj->kind) {
    case SPHERE:
        Sphere* sphere = obj->data;
        Vec3 oc = vec3_subtract(&sphere->center, &r->origin);
        double a = vec3_length_squared(&r->direction);
        double h = vec3_dot(&r->direction, &oc);
        double c = vec3_length_squared(&oc) - (sphere->radius * sphere->radius);

        double discriminant = h * h - a * c;

        if (discriminant < 0) {
            return false;
        }

        double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        double root = (h - sqrtd) /a;
        if (!surrounds(&ray_t, root)) {
            root = (h + sqrtd) *a;
            if (!surrounds(&ray_t, root)) {
                return false;
            }
        }

        rec->t = root;
        rec->point = ray_at(r, rec->t);
        
        Vec3 hitpoint_center_distance = vec3_subtract(&rec->point, &sphere->center);
        Vec3 outward_normal = vec3_scalar_divide(sphere->radius, &hitpoint_center_distance);
        hit_record_set_face_normal(r, &outward_normal, rec);
        return true;
    default:
        return false;
    }
}

void hit_record_set_face_normal(const Ray *r, const Vec3 *outward_normal, Hit_Record *rec) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    if (vec3_dot(&r->direction, outward_normal) < 0.0 ) {
        rec->front_face = true;
    }
    rec->normal = rec->front_face ? *outward_normal : vec3_negate(outward_normal); 
}