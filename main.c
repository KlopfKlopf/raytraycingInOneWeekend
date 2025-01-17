#include "rtweekend.h"
#include "hittables.h"


// Calculate the ray color.
Color ray_color(const Ray *r, const Hittables *world) {
    Hit_Record rec;
    if (hittables_hit(world, r, 0, RT_INFINITY, &rec)) {
        Color color = {1,1,1};
        Color rec_normal = {rec.normal.x, rec.normal.y, rec.normal.z};
        Color normal_color = color_add(&rec_normal, &color);
        return color_scalar_multiply(0.5, &normal_color);
    }
    
    Vec3 unit_direction = vec3_unit_vector(&r->direction);
    Color start_value = {1, 1, 1};
    Color end_value = {0.5, 0.7, 1};
    double a = 0.5 * (unit_direction.y + 1.0);

    Color blended_start_value = color_scalar_multiply((1.0-a), &start_value);
    Color blended_end_value = color_scalar_multiply(a, &end_value);
    Color blended_color = color_add(&blended_start_value, &blended_end_value);
    return blended_color;
}

int main(void) {
    
    double aspect_ratio = (16.0/9.0);
    int image_width = 400;
    
    // Calculate the image height; and ensure that it is at least 1.
    int image_height = (int)(image_width/aspect_ratio);
    if (image_height < 1) {
        image_height = 1;
    }

    //World


    Hittables *world = init_hittables(10);
    Vec3 pos_sp1 = {0,0,-1};
    Vec3 pos_sp2 = {0,-100.5,-1};
    Obj* sp1 = create_object(SPHERE, &pos_sp1);
    Obj* sp2 = create_object(SPHERE, &pos_sp2);
    resize_object(sp1, 0.5, 0.0, 0.0);
    resize_object(sp2, 100.0, 0.0, 0.0);

    hittables_add(world, sp1);
    hittables_add(world, sp2);

    //Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (((double)image_width)/image_height);
    Vec3 camera_center = {0, 0, 0};
    Vec3 focal_point = {0, 0, focal_length};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 viewport_u = {viewport_width, 0, 0};
    Vec3 viewport_v = {0, -viewport_height, 0};
    Vec3 viewport_u_half = vec3_scalar_divide(2, &viewport_u);
    Vec3 viewport_v_half = vec3_scalar_divide(2, &viewport_v);

    //Calculate the horizontal and vertiacl delta vectors from pixel to pixel.

    Vec3 pixel_delta_u = vec3_scalar_multiply((1.0 / (double)image_width), &viewport_u);
    Vec3 pixel_delta_v = vec3_scalar_multiply((1.0/(double)image_height), &viewport_v);

    //Calculate the location opf the upper left pixel.
    Vec3 camera_on_viewport_center = vec3_subtract(&camera_center, &focal_point);
    Vec3 camera_on_leftside = vec3_subtract(&camera_on_viewport_center, &viewport_u_half);
    Vec3 viewport_upper_left = vec3_subtract(&camera_on_leftside, &viewport_v_half);
    Vec3 pixel_delta_point = vec3_add(&pixel_delta_u, &pixel_delta_v);
    Vec3 pixel_padding = vec3_scalar_multiply(0.5, &pixel_delta_point);
    Vec3 pixel00_loc = vec3_add(&viewport_upper_left, &pixel_padding);

    FILE *fstream = fopen("output.ppm", "w");
    if (fstream == NULL) {
        fprintf(stderr, "Error while opening the file.\n");
        return 1;
    }

    fprintf(fstream, "P3\n");
    fprintf(fstream, "%d %d\n", image_width, image_height);
    fprintf(fstream, "255\n");

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            Vec3 pixel_u_pos = vec3_scalar_multiply(i, &pixel_delta_u);
            Vec3 pixel_v_pos = vec3_scalar_multiply(j, &pixel_delta_v);
            Vec3 pixel_pos = vec3_add(&pixel_u_pos, &pixel_v_pos);
            Vec3 pixel_center = vec3_add(&pixel00_loc, &pixel_pos);
            Vec3 ray_direction = vec3_subtract(&pixel_center, &camera_center);
            Ray r = {camera_center, ray_direction};
            
            Color pixel_color = ray_color(&r, world);
            write_color(fstream, &pixel_color);
        }
    }
    fclose(fstream);
    hittables_clear(world);
    return 0;
}