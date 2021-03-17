#pragma once

#include <vector>

void adjacency_lists_compact_storage2(const std::vector<char>& vertexes,
	const std::vector < std::vector<char>>& lists,
	std::vector <char>& vertexes_out,
	std::vector <char>& lists_out,
	std::vector <int>& indexes_out);

void adjacency_lists_compact_storage_refactored2(const std::vector<char>& vertexes,
	const std::vector < std::vector<char>>& lists,
	std::vector <char>& vertexes_out,
	std::vector <char>& lists_out,
	std::vector <int>& indexes_out);

