#pragma once

#include <cmath>
#include <iostream>

#include "../double_comparison/are_equal.h"
#include "../constants_tiptoe.h"
#include "../types_tiptoe/Point.h"
#include "../types_tiptoe/Circle.h"

void test_get_arc_length(double (*algorithm)(const Point&, const Point&, const Circle&));