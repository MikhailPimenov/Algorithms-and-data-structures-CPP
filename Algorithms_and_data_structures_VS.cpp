// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lecture23/adjacency_matrix/adjacency_matrix2.h"
#include "lecture23/adjacency_matrix/test_adjacency_matrix.h"

#include "lecture23/adjacency_lists/adjacency_lists2.h"
#include "lecture23/adjacency_lists/test_adjacency_lists.h"

#include "lecture23/adjacency_lists_compact_storage/adjacency_lists_compact_storage2.h"
#include "lecture23/adjacency_lists_compact_storage/test_adjacency_lists_compact_storage.h"


int main()
{
	std::cout << "\nlecture 23: adjacency matrix\n";
	test_adjacency_matrix(adjacency_matrix2);

	std::cout << "\nlecture 23: adjacency lists\n";
	test_adjacency_lists(adjacency_lists2);

	std::cout << "\nlecture 23: adjacency lists compact storage\n";
	test_adjacency_lists_compact_storage(adjacency_lists_compact_storage2);
	test_adjacency_lists_compact_storage(adjacency_lists_compact_storage_refactored2);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
