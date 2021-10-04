#include "a1.h"


static bool has_one_entering_edge(int current_vertex, const Graph_t &required) {
	return count_entering_edges(current_vertex, required) -
		   count_leaving_edges(current_vertex, required) == 1;
}

static bool has_one_leaving_edge(int current_vertex, const Graph_t& required) {
	return count_leaving_edges(current_vertex, required) -
		count_entering_edges(current_vertex, required) == 1;
}

static bool has_some_undirected_edges(int current_vertex, const Graph_t& required) {
	return count_undirected_edges(current_vertex, required) > 0;
}

static bool has_one_entering_edge_and_some_undirected_edges(int current_vertex, const Graph_t &required) {
	return has_one_entering_edge(current_vertex, required) &&
		   has_some_undirected_edges(current_vertex, required);
}

static bool has_one_leaving_edge_and_some_undirected_edges(int current_vertex, const Graph_t& required) {
	return has_one_leaving_edge(current_vertex, required) &&
		has_some_undirected_edges(current_vertex, required);
}

void change_undirected_to_leaving_edges(int current_vertex, Graph_t& required, const Vertexes_t& undirected_edges) {
	for (int neighbor : undirected_edges)
		required.at(neighbor).erase(current_vertex);
}

void change_undirected_to_entering_edges(int current_vertex, Graph_t& required, const Vertexes_t& undirected_edges) {
	for (int neighbor : undirected_edges)
		required.at(current_vertex).erase(neighbor);
}


/* all incident undirected edges (but not incident REQUIRED undirected) are assigned the direction leaving(entering)...
TODO: need to change UNDECIDED edges, but not REQUIRED edges
*/

void a1(int current_vertex, Graph_t& required, Graph_t& un) {
	if (has_one_entering_edge_and_some_undirected_edges(current_vertex, required)) {
		const auto undirected_edges = get_undirected_edges(current_vertex, required);
		change_undirected_to_leaving_edges(current_vertex, required, undirected_edges);
	}
	
	if (has_one_leaving_edge_and_some_undirected_edges(current_vertex, required)) {
		const auto undirected_edges = get_undirected_edges(current_vertex, required);
		change_undirected_to_entering_edges(current_vertex, required, undirected_edges);
	}
}