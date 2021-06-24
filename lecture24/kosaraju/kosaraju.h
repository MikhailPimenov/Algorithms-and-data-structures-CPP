#ifndef KOSARAJU_H
#define KOSARAJU_H


#include <unordered_map>
#include <unordered_set>
#include <stack>


using Vertex_t     = char;
using Vertexes_t   = std::unordered_set < Vertex_t >;
using Lists_t      = std::unordered_map < Vertex_t, Vertexes_t >;
using Stack_t      = std::stack < Vertex_t >;
using Components_t = std::unordered_map < int, Vertexes_t >;

void reverse_graph ( const Lists_t &adjacency_lists,
                     Lists_t &reversed_adjacency_listsOut );

int kosaraju ( const Lists_t &adjacency_lists );

#endif // KOSARAJU_H
