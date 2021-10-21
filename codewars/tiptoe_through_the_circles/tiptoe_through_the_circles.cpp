#include "tiptoe_through_the_circles.h"

double tiptoe_through_the_circles(Point a, Point b, const std::vector<Circle>& circles) {
	const auto graph = get_graph(a, b, circles);
	return dijkstra_tiptoe(graph, a, b);
}
