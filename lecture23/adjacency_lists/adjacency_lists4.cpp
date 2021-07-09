#include "adjacency_lists4.h"

void adjacency_lists4(std::unordered_map<char, std::unordered_set<char>>& graph) {
	std::cout << "Enter the number of vertexes:";
	int n = 0;
	std::cin >> n;

	std::cout << "Enter the number of edges:";
	int m = 0;
	std::cin >> m;

	for (int i = 0; i < m; ++i) {
		std::cout << "Enter the edge:";
		std::string edge;
		std::cin >> edge;

		char v1 = edge[0];
		char v2 = edge[1];

		if (graph.find(v1) == graph.cend())
			graph.insert(std::pair<char, std::unordered_set<char>>(v1, std::unordered_set<char>()));
		if (graph.find(v2) == graph.cend())
			graph.insert(std::pair<char, std::unordered_set<char>>(v2, std::unordered_set<char>()));
	
		graph.at(v1).insert(v2);
		graph.at(v2).insert(v1);
	}
}
