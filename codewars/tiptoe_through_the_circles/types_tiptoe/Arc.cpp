#include "Arc.h"

Arc::Arc(const Point &a, const Point &b, const Circle &owner)
	: m_a {a},
	  m_b {b},
	  m_length{ get_arc_length(a, b, owner) },
	  m_owner{ owner } {

}

bool operator==(const Arc& arc_1, const Arc& arc_2) noexcept {
	return arc_1.m_a == arc_2.m_a &&
		   arc_1.m_b == arc_2.m_b && 
		   arc_1.m_owner.m_center == arc_2.m_owner.m_center;
}

std::size_t Arc_hash::operator()(const Arc& obj) const noexcept {
	return Point_hash::call(obj.m_a) +
		   Point_hash::call(obj.m_b) +
		   std::hash<double>{}(Hashing_double::multiplier * obj.m_length);
}