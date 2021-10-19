#pragma once

#include <vector>

#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Tangent.h"
#include "../../types_tiptoe.h"

#include "there_is_collision_between_tangent_and_circle.h"

void filter_tangents(Tangents_t& out_tangents, const std::vector<Circle>& circles);