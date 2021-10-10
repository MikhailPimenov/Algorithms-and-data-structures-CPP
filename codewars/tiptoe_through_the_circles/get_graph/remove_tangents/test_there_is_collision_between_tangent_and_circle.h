#pragma once

#include <iostream>

#include "../../types_tiptoe/Circle.h"
#include "../../types_tiptoe/Tangent.h"


void test_there_is_collision_between_tangent_and_circle(
	bool (*algorithm)(const Tangent&, const Circle&)
);

