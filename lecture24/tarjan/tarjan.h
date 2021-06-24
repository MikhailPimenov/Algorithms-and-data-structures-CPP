#ifndef TARJAN_H
#define TARJAN_H

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>

using Vertex_t = char;
using Vertexes_t = std::unordered_set < Vertex_t >;
using Lists_t = std::unordered_map < Vertex_t, Vertexes_t >;
using Stack_t = std::stack < Vertex_t >;
using Numbers_t = std::unordered_map < Vertex_t, int >;

bool tarjan(const Lists_t& adjacency_lists,
	Numbers_t& numbersOut);





#endif // TARJAN_H
