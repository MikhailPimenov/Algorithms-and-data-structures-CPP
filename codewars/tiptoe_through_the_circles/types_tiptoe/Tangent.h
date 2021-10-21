#pragma once

#include "Circle.h"
#include "Point.h"
#include "../get_length/get_distance.h"

struct Tangent {
	Point m_a;
	Point m_b;
	double m_length;
	const Circle* m_circle_a;
	const Circle* m_circle_b;

	Tangent(const Point& a, const Point &b, const Circle &circle_a, const Circle& circle_b);
	friend bool operator==(const Tangent& tangent_1, const Tangent& tangent_2) noexcept;
	friend bool operator!=(const Tangent& tangent_1, const Tangent& tangent_2) noexcept;
};


struct Tangent_hash {
	std::size_t operator()(const Tangent& obj) const noexcept;
};


