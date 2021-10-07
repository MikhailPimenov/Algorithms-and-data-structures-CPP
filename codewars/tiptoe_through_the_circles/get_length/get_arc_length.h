#pragma once

#include <cmath>
#include <numbers>

#include "../constants_tiptoe.h"
#include "../types_tiptoe/Point.h"
#include "../types_tiptoe/Circle.h"

double get_arc_length(const Point& a, const Point& b, const Circle& circle);