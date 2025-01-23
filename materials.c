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

Material* create_metal(const Color albedo, double fuzz) {
    Material *mat = new_material();
    mat->kind = METAL;
    Metal *metal = malloc(sizeof(Metal));
    if (metal == NULL) {
        free(mat);
        exit(1);
    }
    metal->albedo = albedo;
    metal->fuzz = fuzz < 1.0 ? fuzz : 1.0;
    mat->data = metal;
    add_material_ref(mat);
    return mat;
}

Material* create_dielectric(double refraction_idx) {
    Material *mat = new_material();
    mat->kind = DIELECTRIC;
    Dielectric *dielectric = malloc(sizeof(Dielectric));
    if (dielectric == NULL) {
        free(mat);
        exit(1);
    }
    dielectric->refraction_index = refraction_idx;
    mat->data = dielectric;
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
    Material *mat = rec->mat;
    switch (mat->kind) {
        case LAMBERTIAN:
            Vec3 random_unit_vec = vec3_random_unit_vector();
            Vec3 scatter_direction = vec3_add(&rec->normal, &random_unit_vec);

            if (vec3_near_zero(&scatter_direction)) {
                scatter_direction = rec->normal;
            }
            *scattered = (Ray){.origin = rec->point, .direction = scatter_direction};
            *attenuation = ((Lambertian*)mat->data)->albedo;
            return true;
        case METAL:
            Metal * metal_mat = (Metal *)mat->data;
            Vec3 reflected = vec3_reflect(&r->direction, &rec->normal);
            Vec3 random_unit_vector = vec3_random_unit_vector();
            Vec3 fuzzed_unit_vec = vec3_scalar_multiply(metal_mat->fuzz, &random_unit_vector);
            Vec3 reflected_unit_vec = vec3_unit_vector(&reflected);
            reflected = vec3_add(&reflected_unit_vec, &fuzzed_unit_vec);
            *scattered = (Ray){.origin = rec->point, .direction = reflected};
            *attenuation = ((Metal *)mat->data)->albedo;
            return (vec3_dot(&scattered->direction, &rec->normal) > 0);
        case DIELECTRIC:
            Dielectric *refractive_mat = (Dielectric *)mat->data;
            *attenuation = new_color(1.0, 1.0, 1.0);
            double ri;
            if (rec->front_face) {
                ri = (1.0/refractive_mat->refraction_index);
            } else {
                ri = refractive_mat->refraction_index;
            }
            Vec3 unit_direction = vec3_unit_vector(&r->direction);
            Vec3 refracted = vec3_refract(&unit_direction, &rec->normal, ri);
            *scattered = (Ray){.origin = rec->point, refracted};
            return true; 
        default:
            return false;
    }
}