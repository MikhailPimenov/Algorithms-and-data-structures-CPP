#include "count_undirected_edges.h"

int count_undirected_edges(int current_vertex, const Graph_t& graph) {
	int counter = 0;
	for (int neighbor : graph.at(current_vertex))
		if (graph.at(neighbor).find(current_vertex) != graph.at(neighbor).cend())
			++counter;

	return counter;
}