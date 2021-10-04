#include "get_undirected_edges.h"

Vertexes_t get_undirected_edges(int current_vertex, const Graph_t& graph) {
	Vertexes_t result;
	result.reserve(graph.at(current_vertex).size());

	for (int neighbor : graph.at(current_vertex))
		if (graph.at(neighbor).find(current_vertex) != graph.at(neighbor).cend())
			result.insert(neighbor);

	return result;
}