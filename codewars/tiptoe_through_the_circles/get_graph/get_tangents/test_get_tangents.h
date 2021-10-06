#pragma once

#include <iostream>
#include <vector>

#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Point.h"
#include "../../types_tiptoe/Tangent.h"

#include "../../double_comparison/are_equal.h"
#include "../../types_tiptoe.h"


void test_get_tangents(Tangents_t(*algorithm)(const Circle&, const Circle&));

