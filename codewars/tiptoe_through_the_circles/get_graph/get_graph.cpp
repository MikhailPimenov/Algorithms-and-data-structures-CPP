#include "get_graph.h"


Points_on_circles_t get_points(const Tangents_t& tangents) {
	// parsing all tangents to find out which points belongs to which circles
	Points_on_circles_t points;
	for (const auto& tangent : tangents) {
		if (points.find(*tangent.m_circle_a) == points.cend())
			points.insert(std::pair<Circle, Points_t>(*tangent.m_circle_a, Points_t()));
		if (points.find(*tangent.m_circle_b) == points.cend())
			points.insert(std::pair<Circle, Points_t>(*tangent.m_circle_b, Points_t()));

		points.at(*tangent.m_circle_a).insert(tangent.m_a);
		points.at(*tangent.m_circle_b).insert(tangent.m_b);
	}

	return points;
}

Graph_t get_graph(const Point& a, const Point& b, const std::vector <Circle>& circles) {
	
	Tangents_t tangents;
	tangents.reserve(4.0 * (circles.size() + 2u) * (circles.size() + 1u));
	
	// finding all tangents
	for (auto circle_1 = circles.cbegin(); circle_1 != circles.cend(); ++circle_1) {
		for (auto circle_2 = circle_1 + 1u; circle_2 != circles.cend(); ++circle_2) {
			
			// tangents between two circles
			auto pair_tangents = get_tangents(*circle_1, *circle_2);
			
			// removing tangents which can not exist
			filter_tangents(pair_tangents, circles);		
			tangents.insert(pair_tangents.cbegin(), pair_tangents.cend());
		}
	}

	// same with start and finish points and all other circles, considering points as circles
	const Circle circle_a(a, 0.0);
	const Circle circle_b(b, 0.0);
	for (const auto& circle : circles) {
		auto pair_tangents_a = get_tangents(circle_a, circle);
		filter_tangents(pair_tangents_a, circles);

		auto pair_tangents_b = get_tangents(circle, circle_b);
		filter_tangents(pair_tangents_b, circles);

		tangents.insert(pair_tangents_a.cbegin(), pair_tangents_a.cend());
		tangents.insert(pair_tangents_b.cbegin(), pair_tangents_b.cend());
	}

	// same with both start and finish points
	Tangents_t tangent_a_b = get_tangents(circle_a, circle_b);
	filter_tangents(tangent_a_b, circles);
	tangents.insert(tangent_a_b.cbegin(), tangent_a_b.cend());

	// all points with binding to their own circles
	const auto points_on_circles = get_points(tangents);
	
	// finding all arcs
	Arcs_t arcs;
	arcs.reserve(tangents.size() * tangents.size());
	for (const auto& [circle, points_on_circle] : points_on_circles) { 
		auto arcs_on_circle = get_arcs(points_on_circle, circle); 
		arcs.insert(arcs_on_circle.cbegin(), arcs_on_circle.cend());
	}

	// removing arc which can not exist
	filter_arcs(arcs, circles);

	// adding points to graph
	Graph_t graph;
	graph.reserve(tangents.size() * 2u + 2u);
	for (const auto& [_, points_on_circle] : points_on_circles) {
		for (const auto& point : points_on_circle) {
			if (graph.find(point) == graph.cend())
				graph.insert(std::pair<Vertex_t, Vertices_t>(point, Vertices_t()));
		}
	}

	// connecting points with each other according to tangent/arc they belong to
	for (auto& [vertex, neighbors] : graph) {
		for (const auto& tangent : tangents) {
			if (tangent.m_a == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(tangent.m_b, tangent.m_length));
			if (tangent.m_b == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(tangent.m_a, tangent.m_length));
		}
		for (const auto& arc : arcs) {
			if (arc.m_a == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(arc.m_b, arc.m_length));
			if (arc.m_b == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(arc.m_a, arc.m_length));
		}
	}

	return graph;
}
