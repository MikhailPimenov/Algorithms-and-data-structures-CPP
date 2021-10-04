#include "r2.h"

static bool has_only_two_undirected_edges(int current_vertex, const Graph_t& graph) {
	return count_undirected_edges(current_vertex, graph) == 2;
}

static void add_two_undirected_edges(int current_vertex, Graph_t& required, const Vertexes_t& two_neighbors) {
	if (required.find(current_vertex) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t()));

	for (int neighbor : two_neighbors) {
		if (required.find(neighbor) == required.cend())
			required.insert(std::pair<int, Vertexes_t>(neighbor, Vertexes_t()));

		required.at(neighbor).insert(current_vertex);
		required.at(current_vertex).insert(neighbor);
	}		
}

void r2(int current_vertex, const Graph_t& graph, Graph_t& required) {
	if (has_only_two_undirected_edges(current_vertex, graph)) {
		const auto& two_neighbors = graph.at(current_vertex);
		add_two_undirected_edges(current_vertex, required, two_neighbors);
	}
}