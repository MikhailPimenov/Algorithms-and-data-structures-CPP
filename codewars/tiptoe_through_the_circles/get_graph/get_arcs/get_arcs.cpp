#include "get_arcs.h"


Arcs_t get_arcs(const Points_t& points, const Circle& circle) {
	Arcs_t arcs;
	arcs.reserve(points.size() * (points.size() - 1u));

	for (const auto& point_a : points) {
		for (const auto& point_b : points) {
			if (point_a != point_b) {
				arcs.emplace(point_a, point_b, circle);
				arcs.emplace(point_b, point_a, circle);
			}
		}
	}

	return arcs;
}