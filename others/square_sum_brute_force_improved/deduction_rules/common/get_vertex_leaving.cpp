#include "get_vertex_leaving.h"

int get_vertex_leaving(int current_vertex, const Graph_t& graph) {
	return *(graph.at(current_vertex).cbegin());
}