#pragma once

#include "Point.h"

struct Circle {
	const Point m_center;
	const double m_radius;

	Circle();
	Circle(Point center, double radius);
	Circle(double x_center, double y_center, double radius);
};