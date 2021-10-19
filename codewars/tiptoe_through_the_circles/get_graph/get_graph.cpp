#include "get_graph.h"

static void filter_tangents(Tangents_t& tangents, const std::vector<Circle>& circles) {
	for (const auto& circle : circles) {
		for (auto tangent = tangents.cbegin(); tangent != tangents.cend();) {
			if (!(tangent->m_circle_a == &circle) && !(tangent->m_circle_b == &circle)){ // create != for circle, unite these conditions or create separated function
				if (there_is_collision_between_tangent_and_circle(*tangent, circle)) {
					tangent = tangents.erase(tangent);
					continue;
				}
			}
			++tangent;
		}
	}
}
void filter_arcs(Arcs_t& arcs, const std::vector<Circle>& circles) {
	for (const auto& circle : circles) {
		for (auto arc = arcs.cbegin(); arc != arcs.cend();) {
			if (!(arc->m_owner == circle)) {// create != for circle, unite these conditions or create separated function
				if (there_is_collision_between_arc_and_circle(*arc, circle)) {
					arc = arcs.erase(arc);
					continue;
				}
			}
			++arc;
		}
	}
}

std::unordered_map<Circle, Points_t, Circle_hash> get_points(const Tangents_t& tangents) {
	std::unordered_map<Circle, Points_t, Circle_hash> points;
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

// TODO: split into different functions
Graph_t get_graph(const Point& a, const Point& b, const std::vector <Circle>& circles) {
	const Circle circle_a(a, 0.0);
	const Circle circle_b(b, 0.0);

	Tangents_t tangents;
	tangents.reserve(4.0 * (circles.size() + 2u) * (circles.size() + 1u));
	
	for (auto circle_1 = circles.cbegin(); circle_1 != circles.cend(); ++circle_1) {
		for (auto circle_2 = circle_1 + 1u; circle_2 != circles.cend(); ++circle_2) {
			auto pair_tangents = get_tangents(*circle_1, *circle_2);
			filter_tangents(pair_tangents, circles);		
			tangents.insert(pair_tangents.cbegin(), pair_tangents.cend());
		}
	}

	for (const auto& circle : circles) {
		auto pair_tangents_a = get_tangents(circle_a, circle);
		filter_tangents(pair_tangents_a, circles);

		auto pair_tangents_b = get_tangents(circle, circle_b);
		filter_tangents(pair_tangents_b, circles);

		tangents.insert(pair_tangents_a.cbegin(), pair_tangents_a.cend());
		tangents.insert(pair_tangents_b.cbegin(), pair_tangents_b.cend());
	}
	Tangents_t tangent_a_b = get_tangents(circle_a, circle_b);
	filter_tangents(tangent_a_b, circles);
	tangents.insert(tangent_a_b.cbegin(), tangent_a_b.cend());

	const auto points_on_circles = get_points(tangents);
	
	Arcs_t arcs;
	arcs.reserve(tangents.size() * tangents.size());
	for (const auto& [circle, points_on_circle] : points_on_circles) { 
		auto arcs_on_circle = get_arcs(points_on_circle, circle); 
		arcs.insert(arcs_on_circle.cbegin(), arcs_on_circle.cend());
	}
	filter_arcs(arcs, circles);

	Graph_t graph;
	graph.reserve(tangents.size() * 2u + 2u);
	for (const auto& [_, points_on_circle] : points_on_circles) {
		for (const auto& point : points_on_circle) {
			if (graph.find(point) == graph.cend())
				graph.insert(std::pair<Vertex_t, Vertices_t>(point, Vertices_t()));
		}
	}

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
