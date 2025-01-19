#include "color.h"

void write_color(FILE *fstream, const Color *pixel_color){
    double r = pixel_color->r;
    double g = pixel_color->g;
    double b = pixel_color->b;

    // Translate the [0, 1] component values to the byte range [0, 255].
    static const Interval intensity = {.min = 0.000, .max = 0.999};

    int rbyte= (int)256*clamp(&intensity, r);
    int gbyte= (int)256*clamp(&intensity, g);
    int bbyte= (int)256*clamp(&intensity, b);

    fprintf(fstream, "%d %d %d\n", rbyte, gbyte, bbyte);
}

Color color_scalar_multiply(double s, const Color *c) {
    Color result;
    result.r = c->r * s;
    result.g = c->g * s;
    result.b = c->b * s;
    return result;
}

Color color_add(const Color *c1, const Color *c2) {
    Color result;
    result.r = c1->r + c2->r;
    result.g = c1->g + c2->g;
    result.b = c1->b + c2->b;
    return result;
}