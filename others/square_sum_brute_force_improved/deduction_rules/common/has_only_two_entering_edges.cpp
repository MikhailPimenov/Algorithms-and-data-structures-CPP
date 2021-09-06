#include "has_only_two_entering_edges.h"

bool has_only_two_entering_edges(int current_vertex, const Graph_t& graph) {
	int counter = 0;
	for (const auto& [vertex, neighbors] : graph) {
		if (vertex != current_vertex) {
			const auto neighbor = neighbors.find(current_vertex);
			if (neighbor != neighbors.cend()) {
				++counter;
				if (counter > 2)
					return false;
			}
		}
	}

	return counter == 2;
}