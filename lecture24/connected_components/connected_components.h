#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H


#include <unordered_map>
#include <unordered_set>


using Vertex_t = char;
using Vertexes_t = std::unordered_set < Vertex_t >;
using Lists_t = std::unordered_map < Vertex_t, Vertexes_t >;

int connected_components ( const Lists_t &adjacency_lists );


#endif // CONNECTED_COMPONENTS_H
