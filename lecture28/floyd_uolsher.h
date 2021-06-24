#ifndef FLOYD_UOLSHER_H
#define FLOYD_UOLSHER_H


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "common/common.h"


using Vertex3_t        = char;
using Vertexes3_t      = std::unordered_map < Vertex3_t, int >;
using Lists3_t         = std::unordered_map < Vertex3_t, Vertexes3_t >;
using Distances3_t     = std::unordered_map < Vertex3_t, int >;
using All_distances3_t = std::unordered_map < Vertex3_t, Distances3_t >;

void floyd_uolsher ( const Lists3_t &adjacency_lists, All_distances3_t &all_distancesOut );


#endif // FLOYD_UOLSHER_H
