#include "square_sum_brute_force_improved.h"

static Graph_t get_graph(int n) {
	const int max_square = 2 * n - 1;

	/*
	This is vector but not unordered_set because of its order.
	Order is needed to be independend of hash function of unordered_set,
	which determines the order of squares, which then determines the order
	of possible neighbors for each number in graph.
	*/
	std::vector<int> squares; 

	int index = 1;

	while (index * index <= max_square) {
		squares.push_back(index * index);
		++index;
	}

	Graph_t graph;
	for (int number = 1; number < n + 1; ++number)
		graph.insert(std::pair<int, Vertexes_t>(number, Vertexes_t()));
		

	for (auto& [number, neighbors] : graph) {
		for (int neighbor = 1; neighbor < n + 1; ++neighbor) {
			for (int square : squares) {
				if (number + neighbor == square && number != neighbor) {
					neighbors.insert(neighbor);
				}
			}
		}
	}

	return graph;
}
static void depth_first_search(int start, const Graph_t& graph, Vertexes_t& used, std::vector<int> &path) {
	if (path.size() == graph.size())
		throw - 1;

	for (int neighbor : graph.at(start)) {
		if (used.find(neighbor) == used.cend()) {
			path.push_back(neighbor);
			used.insert(neighbor);
			depth_first_search(neighbor, graph, used, path);
			used.erase(neighbor);
			path.pop_back();
		}
	}
}
std::vector < int > square_sum_brute_force_improved(int n) {
	Graph_t graph = get_graph(n);
	Vertexes_t used;
	used.reserve(graph.size());

	std::vector<int> path;
	path.reserve(graph.size());
	
	for (auto& [number, _] : graph) {
		path.push_back(number);
		used.insert(number);
		try {
			depth_first_search(number, graph, used, path);
		}
		catch (int) {
			return path;
		}
		path.clear();
		used.clear();
	}
	
	return std::vector<int>();
}



/*
* Пусть - для каждого 
A 1

B 1

C: A, B => 1 + max(A, B) = 2
B: 1 + C = 3
A: 1 + C = 3

D: 1 + C = 3

E: 1 + D = 4


*/