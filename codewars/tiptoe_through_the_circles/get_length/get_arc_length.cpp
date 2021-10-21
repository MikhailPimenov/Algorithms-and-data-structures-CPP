#include "get_arc_length.h"

double get_arc_length(const Point& a, const Point& b, const Circle& circle) {
	
	const double angle_a = get_angle_with_x_axis(a, circle.m_center);
	const double angle_b = get_angle_with_x_axis(b, circle.m_center);

	// angles from 0 to 2*pi are considered
	const double delta_angle =
		angle_a > angle_b ? angle_a - angle_b : 
		                    2.0 * g_pi + angle_a - angle_b;

	return circle.m_radius * delta_angle;
}