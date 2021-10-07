#include "get_arc_length.h"

double get_arc_length(const Point& a, const Point& b, const Circle& circle) {

	const double angle_a = are_equal(a.m_x, circle.m_center.m_x) ?
		g_pi / 2.0 :
		std::atan((a.m_x - circle.m_center.m_x) / (a.m_y - circle.m_center.m_y));
	const double angle_b = are_equal(b.m_x, circle.m_center.m_x) ?
		g_pi / 2.0 :
		std::atan((b.m_x - circle.m_center.m_x) / (b.m_y - circle.m_center.m_y));

	const double delta_angle =
		angle_a > angle_b ? angle_a - angle_b : 
		                    2.0 * g_pi + angle_a - angle_b;

	return circle.m_radius * delta_angle;
}