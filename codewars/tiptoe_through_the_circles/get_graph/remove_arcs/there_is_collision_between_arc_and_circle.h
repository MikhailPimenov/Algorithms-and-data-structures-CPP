#pragma once

#include "../../get_length/get_distance.h"
#include "../../get_angle/get_angle.h"

#include "../../types_tiptoe/Arc.h"
#include "../../types_tiptoe/Double.h"
#include "../../types_tiptoe/Circle.h"

bool there_is_collision_between_arc_and_circle(const Arc& arc, const Circle& circle);