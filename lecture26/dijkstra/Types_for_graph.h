#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

using Vertex3_t = char;
using Vertexes3_t = std::unordered_map < Vertex3_t, int >;
using Lists3_t = std::unordered_map < Vertex3_t, Vertexes3_t >;
using Queue3_t = std::queue < Vertex3_t >;
using Distances3_t = std::unordered_map < Vertex3_t, int >;