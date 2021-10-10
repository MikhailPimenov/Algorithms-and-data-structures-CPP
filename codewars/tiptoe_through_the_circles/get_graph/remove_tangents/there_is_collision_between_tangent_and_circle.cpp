#include "there_is_collision_between_tangent_and_circle.h"

bool there_is_collision_between_tangent_and_circle(const Tangent& tangent, const Circle& circle) {

	if (get_distance(circle, tangent) > circle.m_radius)
		return false;

	if (is_point_between_points(circle.m_center, tangent.m_a, tangent.m_b))
		return true;

	if (get_distance(circle.m_center, tangent.m_a) > circle.m_radius &&
		get_distance(circle.m_center, tangent.m_b) > circle.m_radius)
		return false;

	return true;
}