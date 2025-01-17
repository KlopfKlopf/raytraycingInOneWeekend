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