#pragma once

#include <cmath>
#include <vector>

#include "../../types_tiptoe/Point.h"
#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Tangent.h"

#include "../../get_length/get_distance.h"

#include "../../double_comparison/are_equal.h"

std::vector<Tangent> get_tangents(const Circle& circle_1, const Circle& circle_2);