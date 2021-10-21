#include "is_point_between_points.h"

// returns true if the projection of point on the line(point_1, point_2) lays between point_1 and point_2
bool is_point_between_points(const Point& point, const Point& point_1, const Point& point_2) {
	if (are_equal(point_1.m_x, point_2.m_x))
		return is_between(point.m_y, point_1.m_y, point_2.m_y);

	const double distance = get_distance(point_1, point_2);

	const double k = ((point_2.m_y - point_1.m_y) * (point.m_x - point_1.m_x) - 
		             (point_2.m_x - point_1.m_x) * (point.m_y - point_1.m_y)) / 
		             (distance * distance);

	const double x_n = point.m_x - k * (point_2.m_y - point_1.m_y);

	return is_between(x_n, point_1.m_x, point_2.m_x);
}