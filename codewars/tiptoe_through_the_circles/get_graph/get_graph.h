#pragma once

#include <unordered_map>

#include "../types_tiptoe/Arc.h"
#include "../types_tiptoe/Circle.h"
#include "../types_tiptoe/Point.h"
#include "../types_tiptoe/Tangent.h"

#include "get_arcs/get_arcs.h"
#include "get_tangents/get_tangents.h"
//#include "remove_arcs/there_is_collision_between_arc_and_circle.h"
//#include "remove_tangents/there_is_collision_between_tangent_and_circle.h"
#include "remove_tangents/filter_tangents.h"
#include "remove_arcs/filter_arcs.h"

#include "../types_tiptoe.h"

Graph_t get_graph(const Point& a, const Point& b, const std::vector <Circle>& circles);
