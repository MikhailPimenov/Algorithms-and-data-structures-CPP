#pragma once

#include <iostream>

#include "../types_tiptoe/Point.h"
#include "../types_tiptoe/Circle.h"

#include "../types_tiptoe.h"

#include "../constants_tiptoe.h"

void test_get_graph(Graph_t (*algorithm)(const Point&, const Point&, const std::vector<Circle>&));