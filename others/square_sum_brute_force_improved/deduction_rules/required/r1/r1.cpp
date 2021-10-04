#include "r1.h"


static void remove_leaving_edge(int current_vertex, int leaving_vertex, Graph_t& undecided) {
	undecided.at(current_vertex).erase(leaving_vertex);
}

static void remove_entering_edge(int current_vertex, int entering_vertex, Graph_t& undecided) {
	undecided.at(entering_vertex).erase(current_vertex);
}

static void add_leaving_edge(int current_vertex, int leaving_vertex, Graph_t& required) {
	if (required.find(current_vertex) == required.cend())
		required.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t()));
	required.at(current_vertex).insert(leaving_vertex);
}

static bool has_only_one_entering_edge(int current_vertex, const Graph_t& graph) {
	int counter = 0;
	for (const auto& [vertex, neighbors] : graph) {
		if (vertex != current_vertex) {
			const auto neighbor = neighbors.find(current_vertex);
			if (neighbor != neighbors.cend()) {
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

static bool has_no_undirected_edges(int current_vertex, const Graph_t& graph) {
	return count_undirected_edges(current_vertex, graph) == 0;
}

static bool has_only_one_leaving_edge_and_no_undirected_edges(int current_vertex, const Graph_t& graph) {
	return has_only_one_leaving_edge(current_vertex, graph) &&
		has_no_undirected_edges(current_vertex, graph);
}

static bool has_only_one_entering_edge_and_no_undirected_edges(int current_vertex, const Graph_t& graph) {
	return has_only_one_entering_edge(current_vertex, graph) &&
		has_no_undirected_edges(current_vertex, graph);
}

//void r1(int current_vertex, const Graph_t& graph, Graph_t &required) {
//	if (has_only_one_leaving_edge_and_no_undirected_edges(current_vertex, graph)) {
//		const int the_only_leaving_neighbor = get_vertex_leaving(current_vertex, graph);
//		add_leaving_edge(current_vertex, the_only_leaving_neighbor, required);
//	}
//	
//	if (has_only_one_entering_edge_and_no_undirected_edges(current_vertex, graph)) {
//		const int the_only_entering_neighbor = get_vertex_entering(current_vertex, graph);
//		add_entering_edge(current_vertex, the_only_entering_neighbor, required);
//	}
//}

void r1(int current_vertex, Graphs_t& graphs) {
	if (has_only_one_leaving_edge_and_no_undirected_edges(current_vertex, graphs.m_graph)) {
		const int the_only_leaving_neighbor = get_vertex_leaving(current_vertex, graphs.m_graph);
		add_leaving_edge(current_vertex, the_only_leaving_neighbor, graphs.m_required);
		remove_leaving_edge(current_vertex, the_only_leaving_neighbor, graphs.m_undecided);
	}

	if (has_only_one_entering_edge_and_no_undirected_edges(current_vertex, graphs.m_graph)) {
		const int the_only_entering_neighbor = get_vertex_entering(current_vertex, graphs.m_graph);
		add_entering_edge(current_vertex, the_only_entering_neighbor, graphs.m_required);
		remove_entering_edge(current_vertex, the_only_entering_neighbor, graphs.m_undecided);
	}
}
