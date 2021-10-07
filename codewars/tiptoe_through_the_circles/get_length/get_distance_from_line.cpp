#include "get_distance_from_line.h"

double get_distance(const Circle& circle, const Tangent& tangent) {
	const double numerator = std::abs(
		(tangent.m_b.m_x - tangent.m_a.m_x) * (tangent.m_a.m_y - circle.m_center.m_y) -
		(tangent.m_a.m_x - circle.m_center.m_x) * (tangent.m_b.m_y - tangent.m_a.m_y)
	);
	const double distance = get_distance(tangent.m_a, tangent.m_b);

	return numerator / distance;
}