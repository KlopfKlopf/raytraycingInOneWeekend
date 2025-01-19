#include "interval.h"

double size(const Interval *i) {
    return i->max - i->min;
}

bool contains(const Interval *i, double x) {
    return i->min <= x && x <= i->max;
}

bool surrounds(const Interval *i, double x) {
    return i->min < x && x < i->max;
}

double clamp(const Interval *i, double x) {
    if (x < i->min) return i->min;
    if (x > i->max) return i->max;
    return x;
}