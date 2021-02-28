// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lecture5/eratosthenes_sieve/eratosthenes_sieve2.h"
#include "lecture5/eratosthenes_sieve/test_eratosthenes_sieve.h"
#include "lecture5/invert_array/invert_array2.h"
#include "lecture5/invert_array/test_invert_array.h"

int main()
{
	std::cout << "\nlecture 5: eratosthenes sieve\n";
	test_eratosthenes_sieve(eratosthenes_sieve2);

	std::cout << "\nlecture 5: invert array\n";
	test_invert_array(invert_array2);
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
