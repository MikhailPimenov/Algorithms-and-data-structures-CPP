#pragma once

#include <iomanip>
#include <iostream>
#include <vector>

#include "types_tiptoe/Circle.h"
#include "types_tiptoe/Double.h"
#include "types_tiptoe/Point.h"

void test_tiptoe_through_the_circles(double (*algorithm)(Point, Point, const std::vector<Circle>&));