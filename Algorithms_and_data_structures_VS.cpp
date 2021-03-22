// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lecture24/connected_components/test_connected_components.h"
#include "lecture24/connected_components/count_connected_components2.h"

#include "lecture24/kosaraju/kosaraju2.h"
#include "lecture24/kosaraju/test_kosaraju.h"

#include "lecture24/tarjan/tarjan2.h"
#include "lecture24/tarjan/test_tarjan.h"
#include "lecture24/tarjan/is_sorted_graph.h"


int main()
{
	std::cout << "\nlecture 24: count connected components:\n";
	test_connected_components(count_connected_components2);

	std::cout << "\nlecture 24: kosaraju:\n";
	test_kosaraju(kosaraju_adapted2);

	std::cout << "\nlecture 24: tarjan\n";
	test_tarjan(tarjan2, is_sorted_graph);

	
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
