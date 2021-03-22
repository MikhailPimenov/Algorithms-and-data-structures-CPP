#pragma once

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Vertex2_t = std::string;
using Vertexes2_t = std::unordered_set < Vertex2_t >;
using Lists2_t = std::unordered_map < Vertex2_t, Vertexes2_t >;
using Queue2_t = std::queue < Vertex2_t >;
using Distances2_t = std::unordered_map < Vertex2_t, int >;
using Path2_t = std::vector < Vertex2_t >;