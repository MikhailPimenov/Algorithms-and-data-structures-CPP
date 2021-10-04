#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

using Vertexes_t = std::unordered_set < int >;
using Graph_t = std::unordered_map < int, Vertexes_t >;

struct Graphs_t {
	const Graph_t m_graph;
	Graph_t m_undecided;
	Graph_t m_required;
	Graph_t m_path;
	Graph_t m_deleted;

	Graphs_t(const Graph_t& graph);
};

std::vector < int > square_sum_brute_force_improved(int n);