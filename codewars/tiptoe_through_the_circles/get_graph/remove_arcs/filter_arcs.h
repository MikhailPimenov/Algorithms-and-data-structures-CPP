#pragma once

#include <vector>

#include "../../types_tiptoe.h"
#include "../../types_tiptoe/Arc.h"
#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Double.h"

#include "there_is_collision_between_arc_and_circle.h"

void filter_arcs(Arcs_t& arcs, const std::vector<Circle>& circles);