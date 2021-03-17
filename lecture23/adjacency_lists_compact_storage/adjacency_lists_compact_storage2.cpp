#include "adjacency_lists_compact_storage2.h"

void adjacency_lists_compact_storage2(const std::vector<char>& vertexes, const std::vector<std::vector<char>>& lists, std::vector<char>& vertexes_out, std::vector<char>& lists_out, std::vector<int>& indexes_out)
{
	std::size_t length = 0;
	for (const auto& subvector : lists)
		length += subvector.size();
	lists_out.resize(length);

	std::size_t index = 0;
	indexes_out.resize(vertexes.size() + 1u);
	indexes_out.at(0) = index;

	for (std::size_t k = 0; k < lists.size(); ++k) {
		for (std::size_t j = 0; j < lists.at(k).size(); ++j) {
			lists_out.at(index) = lists.at(k).at(j);
			++index;
		}
		indexes_out.at(k + 1) = index;
	}
	vertexes_out = vertexes;
}


void adjacency_lists_compact_storage_refactored2(const std::vector<char>& vertexes,
	const std::vector < std::vector<char>>& lists,
	std::vector <char>& vertexes_out,
	std::vector <char>& lists_out,
	std::vector <int>& indexes_out)
{
	std::size_t length = 0;
	for (const auto& subvector : lists)
		length += subvector.size();
	lists_out.reserve(length);

	std::size_t index = 0;
	indexes_out.reserve(vertexes.size() + 1u);
	indexes_out.push_back(index);

	for (const auto& subvector : lists) {
		for (char vertex : subvector) {
			lists_out.push_back(vertex);
			++index;
		}
		indexes_out.push_back(index);
	}
	vertexes_out = vertexes;
}
