#pragma once


#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>

using Vertex_t = char;
using Vertexes_t = std::unordered_set < Vertex_t >;
using Lists_t = std::unordered_map < Vertex_t, Vertexes_t >;
using Stack_t = std::stack < Vertex_t >;
using Distances_t = std::unordered_map < Vertex_t, int >;
using Path_t = std::vector < Vertex_t >;
using Queue_t = std::queue < Vertex_t >;
