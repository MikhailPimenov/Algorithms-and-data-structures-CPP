#pragma once

#include <deque>
#include <unordered_map>
#include <unordered_set>

#include "types_tiptoe/Arc.h"
#include "types_tiptoe/Double.h"
#include "types_tiptoe/Point.h"
#include "types_tiptoe/Tangent.h"

using Length_t = double;

using Length_t_hash = Double_hash;

using Tangents_t = std::unordered_set<Tangent, Tangent_hash>;

using Arcs_t = std::unordered_set<Arc, Arc_hash>;

using Points_t = std::unordered_set<Point, Point_hash>;

using Points_on_circles_t = std::unordered_map<Circle, Points_t, Circle_hash>;

using Vertex_t = Point;

using Vertex_t_hash = Point_hash;

using Vertices_t = std::unordered_multimap<Vertex_t, Length_t, Vertex_t_hash>;

using Queue_t = std::deque<Vertex_t>;

using Distances_t = std::unordered_map<Vertex_t, Length_t, Vertex_t_hash>;;

using Graph_t = std::unordered_map<Vertex_t, Vertices_t, Vertex_t_hash>;