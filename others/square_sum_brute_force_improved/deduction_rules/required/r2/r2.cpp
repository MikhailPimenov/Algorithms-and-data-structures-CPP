#include "r2.h"

static bool has_only_two_leaving_edges(int current_vertex, const Graph_t& graph) {
	return graph.at(current_vertex).size() == 2u;
}

//static bool has_only_two_entering_edges(int current_vertex, const Graph_t& graph) {
//	int counter = 0;
//	for (const auto& [vertex, neighbors] : graph) {
//		if (vertex != current_vertex) {
//			const auto neighbor = neighbors.find(current_vertex);
//			if (neighbor != neighbors.cend()) {
//				++counter;
//				if (counter > 2)
//					return false;
//			}
//		}
//	}
//
//	return counter == 2;
//}

static bool has_only_two_undirected_edges(int current_vertex, const Graph_t& graph) {
	return has_only_two_leaving_edges(current_vertex, graph) && 
		has_only_two_entering_edges(current_vertex, graph);
}

static void add_two_undirected_edges(int current_vertex, Graph_t& required, int neighbor1, int neighbor2) {
	if (required.find(current_vertex) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t()));

	required.at(current_vertex).insert(neighbor1);
	required.at(current_vertex).insert(neighbor2);

	if (required.find(neighbor1) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(neighbor1, Vertexes_t()));
	required.at(neighbor1).insert(current_vertex);

	if (required.find(neighbor2) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(neighbor2, Vertexes_t()));
	required.at(neighbor2).insert(current_vertex);
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