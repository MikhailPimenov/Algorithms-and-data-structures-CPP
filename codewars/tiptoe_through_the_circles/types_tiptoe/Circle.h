#pragma once

#include "Point.h"
#include "../double_comparison/are_equal.h"

struct Circle {
	const Point m_center;
	const double m_radius;

	Circle();
	Circle(Point center, double radius);
	Circle(double x_center, double y_center, double radius);

	friend bool operator==(const Circle& circle_1, const Circle& circle_2);
};

struct Circle_hash {
	std::size_t operator()(const Circle& obj) const noexcept;
};