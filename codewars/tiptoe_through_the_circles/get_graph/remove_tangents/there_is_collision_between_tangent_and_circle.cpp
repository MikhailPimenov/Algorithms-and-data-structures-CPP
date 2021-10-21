#include "there_is_collision_between_tangent_and_circle.h"

bool there_is_collision_between_tangent_and_circle(const Tangent& tangent, const Circle& circle) {

	// circle is far enough from line on which tangent is
	if (get_distance(circle, tangent) > circle.m_radius)
		return false;

	// circle intersects with tangent between tangent's ends
	if (is_point_between_points(circle.m_center, tangent.m_a, tangent.m_b))
		return true;

	// circle covers one of tangent's ends
	if (get_distance(circle.m_center, tangent.m_a) > circle.m_radius &&
		get_distance(circle.m_center, tangent.m_b) > circle.m_radius)
		return false;

	return true;
}