#include <stdlib.h>
#include "camera.h"


Camera* new_camera(double aspect_ratio, int image_width) {
    Camera *cam = calloc(1, sizeof(Camera));
    if (cam == NULL) {
        exit(1);
    }
    cam->aspect_ratio = aspect_ratio;
    cam->image_width = image_width;
    return cam;
}

void initialize(Camera *cam) {
    // Calculate the image height; and ensure that it is at least 1.
    cam->image_height = (int)(cam->image_width/cam->aspect_ratio);
    if (cam->image_height < 1) {
        cam->image_height = 1;
    }

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (((double)cam->image_width)/cam->image_height);
    Vec3 camera_center = new_vec3(0,0,0);
    cam->center = camera_center;
    Vec3 focal_point = new_vec3(0,0,focal_length);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 viewport_u = new_vec3(viewport_width,0,0);
    Vec3 viewport_v = new_vec3(0, -viewport_height, 0);
    Vec3 viewport_u_half = vec3_scalar_divide(2, &viewport_u);
    Vec3 viewport_v_half = vec3_scalar_divide(2, &viewport_v);

    //Calculate the horizontal and vertiacl delta vectors from pixel to pixel.

    cam->pixel_delta_u = vec3_scalar_multiply((1.0 / (double)cam->image_width), &viewport_u);
    cam->pixel_delta_v = vec3_scalar_multiply((1.0/(double)cam->image_height), &viewport_v);

    //Calculate the location opf the upper left pixel.
    Vec3 camera_on_viewport_center = vec3_subtract(&cam->center, &focal_point);
    Vec3 camera_on_leftside = vec3_subtract(&camera_on_viewport_center, &viewport_u_half);
    Vec3 viewport_upper_left = vec3_subtract(&camera_on_leftside, &viewport_v_half);
    Vec3 pixel_delta_point = vec3_add(&cam->pixel_delta_u, &cam->pixel_delta_v);
    Vec3 pixel_padding = vec3_scalar_multiply(0.5, &pixel_delta_point);
    cam->pixel00_loc = vec3_add(&viewport_upper_left, &pixel_padding);
}

void render(Camera *cam, const Hittables *world) {
    initialize(cam);

    FILE *fstream = fopen("output.ppm", "w");
    if (fstream == NULL) {
        fprintf(stderr, "Error while opening the file.\n");
        return;
    }

    fprintf(fstream, "P3\n");
    fprintf(fstream, "%d %d\n", cam->image_width, cam->image_height);
    fprintf(fstream, "255\n");

    for (int j = 0; j < cam->image_height; j++) {
        for (int i = 0; i < cam->image_width; i++) {
            Vec3 pixel_u_pos = vec3_scalar_multiply(i, &cam->pixel_delta_u);
            Vec3 pixel_v_pos = vec3_scalar_multiply(j, &cam->pixel_delta_v);
            Vec3 pixel_pos = vec3_add(&pixel_u_pos, &pixel_v_pos);
            Vec3 pixel_center = vec3_add(&cam->pixel00_loc, &pixel_pos);
            Vec3 ray_direction = vec3_subtract(&pixel_center, &cam->center);
            Ray r = {cam->center, ray_direction};
            
            Color pixel_color = ray_color(&r, world);
            write_color(fstream, &pixel_color);
        }
    }
    fclose(fstream);
}

// Calculate the ray color.
Color ray_color(const Ray *r, const Hittables *world) {
    Hit_Record rec;
    Interval interval = {0, RT_INFINITY};
    if (hittables_hit(world, r, interval, &rec)) {
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