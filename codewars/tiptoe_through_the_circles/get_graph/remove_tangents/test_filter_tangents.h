#pragma once

#include <iostream>
#include <vector>

#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Tangent.h"
#include "../../types_tiptoe.h"

void test_filter_tangents(void (*algorithm)(Tangents_t &, const std::vector<Circle>&));