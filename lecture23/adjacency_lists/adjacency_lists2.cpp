#include "adjacency_lists2.h"

void adjacency_lists2(std::unordered_map<char, std::unordered_set<char>>& lists_out)
{
	std::cout << "Enter number of vertexes:\n";
	int m = 0;
	std::cin >> m;

	std::cout << "Enter number of edges:\n";
	int n = 0;
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::cout << "Enter the edge:\n";
		std::string edge;
		std::cin >> edge;

		for (int j = 0; j < 2; ++j) {
			if (lists_out.find(edge[j]) == lists_out.cend())
				lists_out.insert(std::pair <
					char, std::unordered_set <char> >(
						edge[j], std::unordered_set<char>()));
			lists_out.at(edge[j]).insert(edge[(j + 1) % 2]);

		}
	}
}
