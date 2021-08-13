#include "max_range_linear.h"

static void depth_first_search(
	int start,
	const Graph_t& graph,
	Set_t& used,
	std::size_t& out_current_length,
	int& out_left,
	int& out_right
) {
	used.insert(start);
	++out_current_length;

	if (start < out_left) out_left = start;
	if (start > out_right) out_right = start;

	for (int neighbor : graph.at(start)) {
		if (used.find(neighbor) == used.cend())
			depth_first_search(
				neighbor, 
				graph, 
				used, 
				out_current_length, 
				out_left, 
				out_right
			);
	}
}

void max_range_linear(const int* a, int length, int& out_result_left, int& out_result_right) {
	const Graph_t graph = std::move([a, length]() {
		Graph_t temp; 
		for (int index = 0; index < length; ++index)
			temp.insert(std::pair<int, Set_t>(a[index], Set_t()));

		for (auto& [vertex, neighbors] : temp) {
			if (temp.find(vertex + 1) != temp.cend())
				neighbors.insert(vertex + 1);
			if (temp.find(vertex - 1) != temp.cend())
				neighbors.insert(vertex - 1);
		}

		return temp;
	}()); // immediately invoked lambda expression - to make graph constant

	Set_t used;
	out_result_left = a[0];
	out_result_right = a[0];
	std::size_t max_length = 0;

	for (const auto& [vertex, neighbors] : graph) {
		if (used.find(vertex) == used.cend()) {
			int left = vertex;
			int right = vertex;
			std::size_t current_length = 0;
			depth_first_search(vertex, graph, used, current_length, left, right);

			if (current_length > max_length) {
				max_length = current_length;
				out_result_left = left;
				out_result_right = right;
			}
		}
	}

}