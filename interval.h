#pragma once
#include "rtweekend.h"

typedef struct interval {
    double min;
    double max;
} Interval;

double size(const Interval *i);
bool contains(const Interval *i, double x);
bool surrounds(const Interval *i, double x);
double clamp(const Interval *i, double x);

static const Interval empty = {RT_INFINITY, -RT_INFINITY};
static const Interval universe = {-RT_INFINITY, RT_INFINITY};