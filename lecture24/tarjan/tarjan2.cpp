#include "tarjan2.h"

bool depth_first_search(const Lists_t& graph, Vertex_t vertex, Stack_t& stack, Vertexes_t& used, Vertexes_t& used_for_loop_detection)
{
	used.insert(vertex);
	used_for_loop_detection.insert(vertex);

	for (Vertex_t neighbor : graph.at(vertex)) {

		if (used_for_loop_detection.find(neighbor) != used_for_loop_detection.cend())
			//throw std::exception("LOOOOOOOOOP!!!!!");
			return false;
		if (used.find(neighbor) == used.cend()) {
			bool no_loop = true;
			no_loop = depth_first_search(graph, neighbor, stack, used, used_for_loop_detection);
			if (!no_loop) return false;
		}
	}
	used_for_loop_detection.erase(vertex);
	stack.push(vertex);
	return true;
}
bool tarjan2(const Lists_t& graph, Numbers_t& numbers)
{
	Vertexes_t used;
	Vertexes_t used_for_loop_detection;
	Stack_t stack;
	for (const auto& vertex_and_neighbours : graph) {
		if (used.find(vertex_and_neighbours.first) == used.cend()) {
			bool no_loop = true;
			no_loop = depth_first_search(graph, vertex_and_neighbours.first,
				stack, used, used_for_loop_detection);
			if (!no_loop) return false;
		}
	}

	used.clear();
	int number = 0;
	while (!stack.empty()) {
		if (numbers.find(stack.top()) == numbers.cend())
			numbers.insert(std::pair<Vertex_t, int>(stack.top(), 0));

		numbers.at(stack.top()) = number;
		stack.pop();
		++number;
	}

	return true;
}
