#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

using Vertexes_t = std::unordered_set < int >;
using Graph_t = std::unordered_map < int, Vertexes_t >;

std::vector < int > square_sum_brute_force_improved(int n);