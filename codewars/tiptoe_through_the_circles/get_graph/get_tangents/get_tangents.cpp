#include "get_tangents.h"

std::vector<Tangent> get_tangents(const Circle& circle_1, const Circle& circle_2) {
	if (are_equal(circle_1.m_center.m_x, circle_2.m_center.m_x) &&
		are_equal(circle_1.m_center.m_y, circle_2.m_center.m_y))
		return {};

	bool no_inner_tangents = false;
	if (get_distance(circle_1.m_center, circle_2.m_center) <
		circle_1.m_radius + circle_2.m_radius)
		no_inner_tangents = true;

	const auto& circle_b = 
		circle_2.m_center.m_y >= circle_1.m_center.m_y ? circle_2 : circle_1;  // upper circle
	const auto& circle_a = 
		circle_2.m_center.m_y < circle_1.m_center.m_y ? circle_2 : circle_1;   // lower circle

	std::vector<Tangent> tangents;
	tangents.reserve(4u);

	const double distance_between_cirlces = get_distance(circle_a.m_center, circle_b.m_center);
	const double r_a = circle_a.m_radius;
	const double r_b = circle_b.m_radius;
	const double xo_a = circle_a.m_center.m_x;
	const double yo_a = circle_a.m_center.m_y;
	const double xo_b = circle_b.m_center.m_x;
	const double yo_b = circle_b.m_center.m_y;
	
	const double angle_sum_outer = std::asin((r_b - r_a) / distance_between_cirlces) +
		                           std::asin((xo_b - xo_a) / distance_between_cirlces);
	const double angle_subtraction_outer = std::asin((r_b - r_a) / distance_between_cirlces) -
	                                       std::asin((xo_b - xo_a) / distance_between_cirlces);
	const double angle_sum_inner = std::asin((-r_b - r_a) / distance_between_cirlces) +
                       		       std::asin((xo_b - xo_a) / distance_between_cirlces);
	const double angle_subtraction_inner = std::asin((-r_b - r_a) / distance_between_cirlces) -
		                                   std::asin((xo_b - xo_a) / distance_between_cirlces);


	const Point A_outer_1(
		xo_a + r_a * std::cos(angle_sum_outer),
		yo_a - r_a * std::sin(angle_sum_outer)
	);
	const Point B_outer_1(
		xo_b + r_b * std::cos(angle_sum_outer),
		yo_b - r_b * std::sin(angle_sum_outer)
	);
	tangents.emplace_back(A_outer_1, B_outer_1, circle_a, circle_b);


	if (no_inner_tangents)
		return tangents;


	const Point A_outer_2(
		xo_a - r_a * std::cos(angle_subtraction_outer),
		yo_a - r_a * std::sin(angle_subtraction_outer)
	);
	const Point B_outer_2(
		xo_b - r_b * std::cos(angle_subtraction_outer),
		yo_b - r_b * std::sin(angle_subtraction_outer)
	);
	tangents.emplace_back(A_outer_2, B_outer_2, circle_a, circle_b);


	const Point A_inner_1(
		xo_a + r_a * std::cos(angle_sum_inner),
		yo_a - r_a * std::sin(angle_sum_inner)
	);
	const Point B_inner_1(
		xo_b - r_b * std::cos(angle_sum_inner),
		yo_b + r_b * std::sin(angle_sum_inner)
	);
	tangents.emplace_back(A_inner_1, B_inner_1, circle_a, circle_b);


	const Point A_inner_2(
		xo_a - r_a * std::cos(angle_subtraction_inner),
		yo_a - r_a * std::sin(angle_subtraction_inner)
	);
	const Point B_inner_2(
		xo_b + r_b * std::cos(angle_subtraction_inner),
		yo_b + r_b * std::sin(angle_subtraction_inner)
	);
	tangents.emplace_back(A_inner_2, B_inner_2, circle_a, circle_b);


	return tangents;
}
