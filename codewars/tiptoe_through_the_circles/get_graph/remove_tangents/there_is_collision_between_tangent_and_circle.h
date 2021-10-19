#pragma once

#include "../../get_length/get_distance_from_line.h"
#include "is_point_between_points.h"

#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Double.h"
#include "../../types_tiptoe/Tangent.h"


bool there_is_collision_between_tangent_and_circle(const Tangent& tangent, const Circle& circle);

