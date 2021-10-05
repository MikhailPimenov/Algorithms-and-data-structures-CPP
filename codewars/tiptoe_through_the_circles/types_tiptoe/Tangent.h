#pragma once

#include "Circle.h"
#include "Point.h"
#include "../get_length/get_distance.h"

#include <unordered_set>
#include <numeric>

struct Tangent {
	const Point m_a;
	const Point m_b;
	const double m_length;
	const Circle& m_circle_a;
	const Circle& m_circle_b;

	Tangent(Point a, Point b, const Circle &circle_a, const Circle& circle_b);
	//std::size_t operator()() const { return 1; };

	friend bool operator==(const Tangent& tangent_1, const Tangent& tangent_2);
};


struct Tangent_hash {
	std::size_t operator()(const Tangent& obj) const noexcept;
};


