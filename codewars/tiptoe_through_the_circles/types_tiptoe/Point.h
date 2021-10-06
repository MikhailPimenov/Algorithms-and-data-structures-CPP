#pragma once

#include <functional>

#include "../double_comparison/are_equal.h"
#include "../double_comparison/hashing_double.h"

struct Point {
	const double m_x, m_y;

	Point();
	Point(double x, double y);

	friend bool operator==(const Point &point_1, const Point& point_2) noexcept;
};

struct Point_hash {
	std::size_t operator()(const Point& obj) const noexcept;
	static std::size_t call(const Point& obj) noexcept;
};