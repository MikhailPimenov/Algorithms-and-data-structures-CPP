#pragma once

#include <iostream>
#include <vector>

#include "double_comparison/are_equal.h"
#include "types_tiptoe/Circle.h"
#include "types_tiptoe/Point.h"

void test_tiptoe_through_the_circles(double (*algorithm)(Point, Point, const std::vector<Circle>&));