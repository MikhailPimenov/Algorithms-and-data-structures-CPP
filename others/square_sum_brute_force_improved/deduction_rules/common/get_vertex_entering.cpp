#include "get_vertex_entering.h"

int get_vertex_entering(int current_vertex, const Graph_t& graph) {
	for (const auto& [vertex, neighbors] : graph)
		if (neighbors.find(current_vertex) != neighbors.cend())
			return vertex;
}