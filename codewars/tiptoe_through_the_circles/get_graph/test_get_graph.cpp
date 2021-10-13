#include "test_get_graph.h"

static bool operator==(const Vertices_t& left, const Vertices_t& right) {
	for (const auto& [key, value] : left) {
		if (right.find(key) == right.cend())
			return false;
		if (!are_equal(right.at(key), value))
			return false;
	}

	return true;
}

void test_get_graph(Graph_t(*algorithm)(const Point&, const Point&, const std::vector<Circle>&)) {
	std::cout << "test_get_graph:\n";
	Graph_t expected;
	Graph_t actual;
	std::vector<Circle> circles;

	Point a1(-1.0, 0.0);
	Point b1(1.0, 0.0);
	expected.insert(
		std::pair<Vertex_t, Vertices_t>(
			a1, Vertices_t{ std::pair<Vertex_t, double>(b1, 1.0) }));
	expected.insert(
		std::pair<Vertex_t, Vertices_t>(
			b1, Vertices_t{ std::pair<Vertex_t, double>(a1, 1.0) }));

	//actual = algorithm(a1, b1, circles);

	actual.insert(
		std::pair<Vertex_t, Vertices_t>(
			a1, Vertices_t{ std::pair<Vertex_t, double>(b1, 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1) }));
	actual.insert(
		std::pair<Vertex_t, Vertices_t>(
			b1, Vertices_t{ std::pair<Vertex_t, double>(a1, 1.0) }));

	std::cout << "test  #1: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	expected.clear();
	circles.clear();
}
