#include "color.h"

void write_color(FILE *fstream, const Color *pixel_color){
    double r = pixel_color->r;
    double g = pixel_color->g;
    double b = pixel_color->b;

    // Apply a linear to gamma transform for gamma 2

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    // Translate the [0, 1] component values to the byte range [0, 255].
    static const Interval intensity = {.min = 0.000, .max = 0.999};

    int rbyte= (int)256*clamp(&intensity, r);
    int gbyte= (int)256*clamp(&intensity, g);
    int bbyte= (int)256*clamp(&intensity, b);

    fprintf(fstream, "%d %d %d\n", rbyte, gbyte, bbyte);
}

Color color_multiply(Color *c1, Color *c2) {
    Color result;
    result.r = c1->r * c2->r;
    result.g = c1->g * c2->g;
    result.b = c1->b * c2->b;
    return result;
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

Color new_color(double r, double g, double b) {
    Color color = {.r = r, .g = g, .b = b};
    return color;
}

double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return sqrt(linear_component);
    }
    return 0.0;
}