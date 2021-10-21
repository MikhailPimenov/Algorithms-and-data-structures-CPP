#pragma once

#include "types_tiptoe/Circle.h"
#include "types_tiptoe/Point.h"

#include "types_tiptoe.h"
#include "get_graph/get_graph.h"
#include "dijkstra/dijkstra_tiptoe.h"

double tiptoe_through_the_circles(Point a, Point b, const std::vector<Circle>& circles);
