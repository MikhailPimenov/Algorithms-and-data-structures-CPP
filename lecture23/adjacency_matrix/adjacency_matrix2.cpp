#include "adjacency_matrix2.h"

namespace Adjacency_matrix2 {
	int find(char element, char* array, int length) {
		for (int index = 0; index < length; ++index)
			if (array[index] == element)
				return index;

		return -1;
	}
}


int adjacency_matrix2(int*& matrix, char*& vertexes, int*& indexes)
{
	std::cout << "Enter number of vertexes:\n";
	int m;
	std::cin >> m;

	std::cout << "Enter number of edges:\n";
	int n;
	std::cin >> n;


	matrix = new int[(m + 1) * (m + 1)];
	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < m + 1; ++j)
			matrix[i * (m + 1) + j] = 0;
	}

	vertexes = new char[m];
	indexes = new int[m];

	int v_length = 0;
	for (int i = 0; i < n; ++i) {
		std::cout << "Enter edge:\n";
		std::string edge;
		std::cin >> edge;

		int index0 = 0;
		int index1 = 0;
		int find_index = Adjacency_matrix2::find(edge[0], vertexes, v_length);
		if (find_index == -1) {
			vertexes[v_length] = edge[0];
			indexes[v_length] = v_length + 1;
			index0 = v_length + 1;
			++v_length;
		}
		else index0 = indexes[find_index];

		find_index = Adjacency_matrix2::find(edge[1], vertexes, v_length);
		if (find_index == -1) {
			vertexes[v_length] = edge[1];
			indexes[v_length] = v_length + 1;
			index1 = v_length + 1;
			++v_length;
		}
		else index1 = indexes[find_index];

		matrix[index0 * (m + 1) + index1] += 1;
		matrix[index1 * (m + 1) + index0] += 1;


	}

	return -1;
}
