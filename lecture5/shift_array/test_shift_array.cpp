#include "test_shift_array.h"

void test_shift_array(void(*algorithm)(int*, int, int))
{
	int array1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int length1 = sizeof(array1) / sizeof(array1[0]);

	int result1[] = { 5, 6, 7, 0, 1, 2, 3, 4 };
	int shift1 = 3;
	algorithm(array1, length1, shift1);
	std::cout << "test#1: " << (Common::is_equal(array1, result1, length1) ? "ok" : "FAILED") << '\n';


	int array2[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int length2 = sizeof(array2) / sizeof(array2[0]);

	int result2[] = { 6, 7, 0, 1, 2, 3, 4, 5 };
	int shift2 = 18;
	algorithm(array2, length2, shift2);
	std::cout << "test#2: " << (Common::is_equal(array2, result2, length2) ? "ok" : "FAILED") << '\n';


	int array3[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int length3 = sizeof(array3) / sizeof(array3[0]);

	int result3[] = { 3, 4, 5, 6, 7, 0, 1, 2 };
	int shift3 = -3;
	algorithm(array3, length3, shift3);
	std::cout << "test#3: " << (Common::is_equal(array3, result3, length3) ? "ok" : "FAILED") << '\n';


	int array4[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int length4 = sizeof(array4) / sizeof(array4[0]);

	int result4[] = { 2, 3, 4, 5, 6, 7, 0, 1 };
	int shift4 = -18;
	algorithm(array4, length4, shift4);
	std::cout << "test#4: " << (Common::is_equal(array4, result4, length4) ? "ok" : "FAILED") << '\n';	
}
