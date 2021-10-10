#include "get_angle.h"

double get_angle_with_x_axis(const Point& left_side, const Point& center) {
	if (are_equal(left_side.m_x, center.m_x)) {
		if (left_side.m_y < center.m_y)
			return 3.0 * g_pi / 2.0;
		return g_pi / 2.0;
	}

	const double angle = atan((left_side.m_y - center.m_y) / (left_side.m_x - center.m_x));
	
	if (left_side.m_x < center.m_x) 
		return angle + g_pi;

	if (left_side.m_y < center.m_y)
		return angle + 2.0 * g_pi;

	return angle;
}