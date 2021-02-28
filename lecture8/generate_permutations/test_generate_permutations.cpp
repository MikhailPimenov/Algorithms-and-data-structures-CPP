#include "test_generate_permutations.h"

void test_generate_permutations(void (*algorithm) (const int*, int, int))
{
	std::cout << "test_generate_permutations:\n";

	std::cout << "\ntest #1:\n";
	int elements1[]{ 1, 2, 3, 4 };
	int length1 = sizeof(elements1) / sizeof(elements1[0]);
	algorithm(elements1, length1, 2);

	std::cout << "\ntest #2:\n";
	int elements2[]{ 1, 1, 3, 4 };
	int length2 = sizeof(elements2) / sizeof(elements2[0]);
	algorithm(elements2, length2, 2);

	std::cout << "\ntest #3:\n";
	int elements3[]{ 1, 1, 3, 4 };
	int length3 = sizeof(elements3) / sizeof(elements3[0]);
	algorithm(elements3, length3, 3);

	std::cout << "\ntest #4:\n";
	int elements4[]{ 1, 1, 3, 4 };
	int length4 = sizeof(elements4) / sizeof(elements4[0]);
	algorithm(elements4, length4, 4);
}
