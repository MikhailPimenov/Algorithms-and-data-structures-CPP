#pragma once

#include <unordered_map>
#include <unordered_set>

using Vertex3_t = char;
using Vertexes3_t = std::unordered_map < Vertex3_t, int >;
using Lists3_t = std::unordered_map < Vertex3_t, Vertexes3_t >;
using Distances3_t = std::unordered_map < Vertex3_t, int >;
using Vertexes_and_numbers3_t = Distances3_t;
using All_distances3_t = std::unordered_map < Vertex3_t, Distances3_t >;
