#pragma once

#include <vector>

struct Point {
	double m_x, m_y;

	Point();
	Point(double x, double y);
};

struct Circle {
	Point m_center;
	double m_radius;

	Circle();
	Circle(Point center, double radius);
	Circle(double x_center, double y_center, double radius);
};