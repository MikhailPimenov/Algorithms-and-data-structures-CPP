#pragma once

#include <unordered_map>
#include <unordered_set>

using Set_t = std::unordered_set<int>;
using Graph_t = std::unordered_map<int, Set_t>;

void max_range_linear(const int* a, int length, int& out_left, int& out_right);