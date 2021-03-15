// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "lecture17/discrete_bag/discrete_bag2.h"
#include "lecture17/discrete_bag/test_discrete_bag.h"
#include "lecture17/fibonacci_recursive_cash/fibonacci_recursive_cache2.h"
#include "lecture17/fibonacci_recursive_cash/test_fibonacci_recursive_cash.h"

int main()
{
	std::cout << "\nlecture 17: discrete bag\n";
	test_discrete_bag(discrete_bag_adapted2);
	std::cout << "\nlecture 17: fibonacci recursive cache\n";
	Fibonacci_recursive_cache2::initialize_cache();
	test_fibonacci_recursive_cash(fibonacci_recursive_cache2);

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
