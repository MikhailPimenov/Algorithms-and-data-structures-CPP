#pragma once

#include <unordered_set>

#include "types_tiptoe/Tangent.h"
#include "types_tiptoe/Arc.h"

using Tangents_t = std::unordered_set<Tangent, Tangent_hash>;

using Arcs_t = std::unordered_set<Arc, Arc_hash>;

using Points_t = std::unordered_set<Point, Point_hash>;
