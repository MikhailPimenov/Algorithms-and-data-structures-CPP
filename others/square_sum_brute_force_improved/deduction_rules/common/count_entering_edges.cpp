#include "count_entering_edges.h"

int count_entering_edges(int current_vertex, const Graph_t& graph) {
	int counter = 0;
	for (const auto& [_, neighbors] : graph)
		if (neighbors.find(current_vertex) != neighbors.cend())
			++counter;

	return counter;
}