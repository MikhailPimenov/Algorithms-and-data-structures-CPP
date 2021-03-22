#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

using Vertex_t = char;
using Vertexes_t = std::unordered_set < Vertex_t >;
using Lists_t = std::unordered_map < Vertex_t, Vertexes_t >;
using Components_t = std::vector < Vertexes_t >;
using Stack_t = std::stack < Vertex_t >;
using Numbers_t = std::unordered_map<Vertex_t, int>;




