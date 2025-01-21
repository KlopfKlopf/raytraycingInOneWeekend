#pragma once
#include <stdio.h>
#include "interval.h"

typedef struct color {
    double r;
    double g;
    double b;
} Color;

void write_color(FILE *fstream, const Color *pixel_color);
Color color_scalar_multiply(double s, const Color *c);
Color color_add(const Color *c1, const Color *c2);
Color new_color(double r, double g, double b);
double linear_to_gamma(double linear_component);