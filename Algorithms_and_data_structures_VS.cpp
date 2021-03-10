// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "lecture12/levenstein/levenstein2.h"
#include "lecture12/levenstein/test_levenstein.h"
#include "lecture12/knuth_morris_pratt/p_function2.h"
#include "lecture12/knuth_morris_pratt/test_p_function.h"
#include "lecture12/knuth_morris_pratt/knuth_morris_pratt2.h"
#include "lecture12/knuth_morris_pratt/test_find_substring.h"


int main()
{
	std::cout << "\nlecture 12: levenstein\n";
	test_levenstein(levenstein_adapted2);

	std::cout << "\nlecture 12: p_function\n";
	test_p_function(p_function2);

	std::cout << "\nlecture 12: knuth_morris_pratt2\n";
	test_find_substring(knuth_morris_pratt2);
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
