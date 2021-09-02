#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

using Vertexes_t = std::unordered_set < int >;
//using Graph_t = std::unordered_map < int, std::vector < int > >;
using Graph_t = std::vector < std::vector < int > >;


std::vector < int > square_sum_brute_force_improved(int n);