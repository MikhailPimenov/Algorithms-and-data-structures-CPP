#pragma once

#include "Circle.h"
#include "Point.h"
#include "../get_length/get_distance.h"

struct Tangent {
	const Point m_a;
	const Point m_b;
	const double m_length;
	const Circle& m_circle_a;
	const Circle& m_circle_b;

	Tangent(Point a, Point b, const Circle &circle_a, const Circle& circle_b);
};