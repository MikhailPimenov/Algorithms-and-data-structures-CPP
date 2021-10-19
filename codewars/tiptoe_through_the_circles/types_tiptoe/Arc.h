#pragma once

#include "../types_tiptoe/Double.h"
#include "../types_tiptoe/Circle.h"
#include "../types_tiptoe/Point.h"
#include "../get_length/get_arc_length.h"


struct Arc {
	const Point m_a;
	const Point m_b;
	const double m_length;
	const Circle& m_owner;

	Arc(const Point& a, const Point& b, const Circle& owner);

	friend bool operator==(const Arc& arc_1, const Arc& arc_2) noexcept;
};

struct Arc_hash {
	std::size_t operator()(const Arc& obj) const noexcept;
};