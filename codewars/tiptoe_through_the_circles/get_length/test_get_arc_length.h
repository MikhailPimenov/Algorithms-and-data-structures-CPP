#pragma once

#include <cmath>
#include <iostream>

#include "../constants_tiptoe.h"
#include "../types_tiptoe/Double.h"
#include "../types_tiptoe/Circle.h"
#include "../types_tiptoe/Point.h"

void test_get_arc_length(double (*algorithm)(const Point&, const Point&, const Circle&));