#pragma once

#include <iostream>
#include <vector>

#include "../../types_tiptoe.h"
#include "../../types_tiptoe/Arc.h"
#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Double.h"
#include "../../types_tiptoe/Point.h"

void test_filter_arcs(void (*algorithm)(Arcs_t&, const std::vector<Circle>&));