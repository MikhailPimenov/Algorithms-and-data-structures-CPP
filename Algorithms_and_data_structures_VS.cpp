// Algorithms_and_data_structures_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "common_tests/test_sort/test_sort.h"
#include "lecture6/bubble_sort/bubble_sort2.h"
#include "lecture6/insert_sort/insert_sort2.h"
#include "lecture6/select_sort/select_sort2.h"
#include "lecture9/hoar_sort/hoar_sort2.h"
#include "lecture9/merge_sort/merge_sort2.h"
#include "lecture19/heap_sort/heap_sort2.h"


int main()
{
	std::cout << "\nlecture 6: bubble sort\n";
	test_sort(bubble_sort2);
	std::cout << "\nlecture 6: insert sort\n";
	test_sort(insert_sort2);
	std::cout << "\nlecture 6: select sort\n";
	test_sort(select_sort2);
	std::cout << "\nlecture 9: hoar sort\n";
	test_sort(hoar_sort2);
	std::cout << "\nlecture 9: merge sort\n";
	test_sort(merge_sort2);
	std::cout << "\nlecture 19: heap sort\n";
	test_sort(heap_sort2);
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
