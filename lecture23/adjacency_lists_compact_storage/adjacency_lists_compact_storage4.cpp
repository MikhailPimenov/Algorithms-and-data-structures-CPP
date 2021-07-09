#include "adjacency_lists_compact_storage4.h"

void adjacency_lists_compact_storage4(const std::vector<char>& vertexes, const std::vector<std::vector<char>>& lists, std::vector<char>& vertexes_out, std::vector<char>& compact_lists_out, std::vector<int>& indexes_out) {
	int start_index = 0;
	int length = 0;
	for (const auto& list : lists)
		length += list.size();

	vertexes_out = vertexes;
	indexes_out.reserve(vertexes.size() + 1);
	indexes_out.push_back(0);
	compact_lists_out.reserve(length);

	for (const auto& list : lists) {
		for (char neighbor : list) {
			compact_lists_out.push_back(neighbor);
			++start_index;
		}

		indexes_out.push_back(start_index);
	}
}
