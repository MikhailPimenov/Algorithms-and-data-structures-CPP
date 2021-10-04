#include "count_leaving_edges.h"

int count_leaving_edges(int current_vertex, const Graph_t& graph) {
	return graph.at(current_vertex).size();
}