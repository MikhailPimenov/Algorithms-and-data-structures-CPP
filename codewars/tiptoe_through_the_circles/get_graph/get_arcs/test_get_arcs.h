#pragma once

#include <iostream>

#include "../../types_tiptoe/Point.h"
#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Arc.h"
#include "../../types_tiptoe.h"

void test_get_arcs(Arcs_t(*algorithm)(const Points_t&, const Circle&));