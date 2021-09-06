#include "r1.h"

static bool has_only_one_leaving_edge(int current_vertex, const Graph_t& graph) {
	return graph.at(current_vertex).size() == 1u;
}

static void add_leaving_edge(int current_vertex, const Graph_t& graph, Graph_t& required) {
	if (required.find(current_vertex) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t()));
	required.at(current_vertex).insert(*(graph.at(current_vertex).begin()));
}

static bool has_only_one_entering_edge(int current_vertex, const Graph_t& graph, int& out_entering_neighbor) {
	int counter = 0;
	for (const auto& [vertex, neighbors] : graph) {
		if (vertex != current_vertex) {
			const auto neighbor = neighbors.find(current_vertex);
			if (neighbor != neighbors.cend()) {
				if (!counter)
					out_entering_neighbor = vertex;

				++counter;
				if (counter > 1)
					return false;
			}
		}
	}

	return counter == 1;
}

static void add_entering_edge(int current_vertex, int entering_vertex, Graph_t& required) {
	if (required.find(entering_vertex) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(entering_vertex, Vertexes_t()));
	required.at(entering_vertex).insert(current_vertex);
}

void r1(int current_vertex, const Graph_t& graph, Graph_t &required) {
	if (has_only_one_leaving_edge(current_vertex, graph)) {
		add_leaving_edge(current_vertex, graph, required);
	}
	
	int the_only_neighbor;
	if (has_only_one_entering_edge(current_vertex, graph, the_only_neighbor)) {
		add_entering_edge(current_vertex, the_only_neighbor, required);
	}
}

