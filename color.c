#include "color.h"
 
void write_color(FILE *fstream, const Color *pixel_color){
    double r = pixel_color->r;
    double g = pixel_color->g;
    double b = pixel_color->b;

    int rbyte= (int)255.999*r;
    int gbyte= (int)255.999*g;
    int bbyte= (int)255.999*b;

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