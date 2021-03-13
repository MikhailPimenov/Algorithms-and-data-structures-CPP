// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "lecture13/brace_sequence/brace_sequence2.h"
#include "lecture13/brace_sequence/test_brace_sequence.h"
#include "lecture13/reversed_polish_notation/reversed_polish_notation2.h"
#include "lecture13/reversed_polish_notation/test_reversed_polish_notation.h"

int main()
{
	std::cout << "\nlecture 13: brace sequence\n";
	test_brace_sequence(brace_sequence_adapted2);

	std::cout << "\nlecture 13: reversed polish notation\n";
	test_reversed_polish_notation(reversed_polish_notation2);

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
