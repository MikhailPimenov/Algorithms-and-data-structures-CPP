#pragma once

#include "Double.h"

struct Point {
	Double m_x, m_y;

	Point();
	Point(const Double& x, const Double& y);

	friend bool operator==(const Point& point_1, const Point& point_2) noexcept;
	friend bool operator!=(const Point& point_1, const Point& point_2) noexcept;

};

struct Point_hash {
	std::size_t operator()(const Point& obj) const noexcept;
	static std::size_t call(const Point& obj) noexcept;
};