#include "materials.h"

Material* new_material(void) {
    Material *mat = malloc(sizeof(Material));
    if (mat == NULL) {
        exit(1);
    }
    mat->refcount = 0;
    return mat;
}

Material* create_lambertian(const Color albedo) {
    Material *mat = new_material();
    mat->kind = LAMBERTIAN;
    Lambertian *lamb = malloc(sizeof(Lambertian));
    if (lamb == NULL) {
        free(mat);
        exit(1);
    }
    lamb->albedo = albedo;
    mat->data = lamb;
    add_material_ref(mat);
    return mat;
}

Material* create_metal(const Color albedo) {
    Material *mat = new_material();
    mat->kind = METAL;
    Metal *metal = malloc(sizeof(Metal));
    if (metal == NULL) {
        free(mat);
        exit(1);
    }
    metal->albedo = albedo;
    mat->data = metal;
    add_material_ref(mat);
    return mat;
}

void add_material_ref(Material *mat) {
    if (mat == NULL) {
        return;
    }
    mat->refcount++;
}

void remove_material_ref(Material *mat) {
    if (mat == NULL) {
        return;
    }
    mat->refcount--;
    if (mat->refcount == 0) {
        free_material_data(mat);
        free(mat);
    }
}

void free_material_data(Material *mat) {
    if (mat->data == NULL) {
        return;
    }
    free(mat->data);
}

bool scatter(const Ray *r, const Hit_Record *rec, Color *attenuation, Ray *scattered) {
    switch (rec->mat->kind) {
        case LAMBERTIAN:
            Vec3 random_unit_vec = vec3_random_unit_vector();
            Vec3 scatter_direction = vec3_add(&rec->normal, &random_unit_vec);

            if (vec3_near_zero(&scatter_direction)) {
                scatter_direction = rec->normal;
            }
            *scattered = (Ray){.origin = rec->point, .direction = scatter_direction};
            //scattered->origin = rec->point;
            //scattered->direction = scatter_direction;
            *attenuation = ((Lambertian*)rec->mat->data)->albedo;
            return true;
        case METAL:
            Vec3 reflected = vec3_reflect(&r->direction, &rec->normal);
            *scattered = (Ray){.origin = rec->point, .direction = reflected};
            //scattered->origin = rec->point;
            //scattered->direction = reflected;
            *attenuation = ((Metal *)rec->mat->data)->albedo;
            return true;
        default:
            return false;
    }
}