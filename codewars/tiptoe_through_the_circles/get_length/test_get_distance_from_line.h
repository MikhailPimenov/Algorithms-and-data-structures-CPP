#pragma once

#include <iostream>

#include "../double_comparison/are_equal.h"
#include "../types_tiptoe/Circle.h"
#include "../types_tiptoe/Tangent.h"

void test_get_distance_from_line(double (*algorithm)(const Circle&, const Tangent&));