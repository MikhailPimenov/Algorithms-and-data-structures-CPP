#ifndef DISTANCES_H
#define DISTANCES_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using Vertex_t     = char;
using Vertexes_t   = std::unordered_set < Vertex_t >;
using Lists_t      = std::unordered_map < Vertex_t, Vertexes_t >;
using Queue_t      = std::queue < Vertex_t >;
using Distances_t  = std::unordered_map < Vertex_t, int >;

void distances ( const Lists_t &adjacency_lists, Distances_t &distancesOut, Vertex_t start );

#endif // DISTANCES_H
