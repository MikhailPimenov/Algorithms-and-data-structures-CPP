#include "has_only_one_leaving_edge.h"

static int count_leaving_edges(int current_vertex, const Graph_t& graph) {
	return graph.at(current_vertex).size();
}

static int count_entering_edges(int current_vertex, const Graph_t& graph) {
	int counter = 0;
	for (const auto& [_, neighbors] : graph)
		if (neighbors.find(current_vertex) != neighbors.cend())
			++counter;

	return counter;
}

bool has_only_one_leaving_edge(int current_vertex, const Graph_t& graph) {
	return graph.at(current_vertex).size() == 1u;
	//return (count_leaving_edges(current_vertex, graph) - 
		    //count_entering_edges(current_vertex, graph)) == 1;

}