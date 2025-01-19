#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory.h>
#include <stdbool.h>

#define RT_INFINITY HUGE_VAL
#define PI 3.141592653589793

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

inline static double random_double(void) {
    return rand() / (RAND_MAX + 1.0);
}

inline static double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}