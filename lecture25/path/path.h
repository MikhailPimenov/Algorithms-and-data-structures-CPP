#ifndef PATH_H
#define PATH_H


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

using Vertex_t     = char;
using Vertexes_t   = std::unordered_set < Vertex_t >;
using Lists_t      = std::unordered_map < Vertex_t, Vertexes_t >;
using Queue_t      = std::queue < Vertex_t >;
using Distances_t  = std::unordered_map < Vertex_t, int >;
using Path_t       = std::vector < Vertex_t >;


void path ( const Lists_t &adjacency_lists, Path_t &pathOut, Vertex_t start, Vertex_t finish );

#endif // PATH_H
