// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "lecture11/chess_queen/chess_queen2.h"
#include "lecture11/chess_queen/test_chess_queen.h"
#include "lecture11/longest_common_subsequence/longest_common_subsequence2.h"
#include "lecture11/longest_common_subsequence/test_longest_common_subsequence.h"
#include "lecture11/longest_increasing_subsequence/longest_increasing_subsequence2.h"
#include "lecture11/longest_increasing_subsequence/test_longest_increasing_subsequence.h"

int main()
{
	std::cout << "\nlecture 11: chess queen\n";
	test_chess_queen(chess_queen2);
	std::cout << "\nlecture 11: longest common subsequence\n";
	test_longest_common_subsequence(longest_common_subsequence2);
	std::cout << "\nlecture 11: longest increasing subsequence\n";
	test_longest_increasing_subsequence(longest_increasing_subsequence2);
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
