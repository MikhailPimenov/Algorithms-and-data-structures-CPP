#include "test_longest_common_subsequence.h"



void test_longest_common_subsequence(int(*algorithm)(const int*, int, const int*, int, int*&))
{
	std::cout << "test_largest_common_subsequence:\n";

	int sequence11[] = { 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5 };
	int length11 = sizeof(sequence11) / sizeof(sequence11[0]);

	int sequence12[] = { 9, 9, 9, 1, 9, 9, 9, 2, 9, 9, 9, 3, 9, 9, 9, 4, 9, 9, 9, 5 };
	int length12 = sizeof(sequence12) / sizeof(sequence12[0]);

	int subsequence1[] = { 1, 2, 3, 4, 5 };
	int length1 = sizeof(subsequence1) / sizeof(subsequence1[0]);

	int* result_subsequence = nullptr;
	int result_length = 0;

	result_length = algorithm(sequence11, length11, sequence12, length12, result_subsequence);
	std::cout << "test #1: " << ((result_length == length1) ? "ok" : "FAILED") << '\n';
	std::cout << "test #1.1: "
		<< ((Common::is_equal(subsequence1, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence21[] = { 0, 1, 0, 0, 2, 0, 3, 0, 4, 0, 5 };
	int length21 = sizeof(sequence21) / sizeof(sequence21[0]);

	int sequence22[] = { 9, 1, 9, 2, 3, 4, 5, 9, 9 };
	int length22 = sizeof(sequence22) / sizeof(sequence22[0]);

	int subsequence2[] = { 1, 2, 3, 4, 5 };
	int length2 = sizeof(subsequence2) / sizeof(subsequence2[0]);

	result_length = algorithm(sequence21, length21, sequence22, length22, result_subsequence);
	std::cout << "test #2: " << ((result_length == length2) ? "ok" : "FAILED") << '\n';
	std::cout << "test #2.1: "
		<< ((Common::is_equal(subsequence2, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence31[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						  0,  1,  0,  0,  2,  0,  3,  0,  4,  0, 5 };
	int length31 = sizeof(sequence31) / sizeof(sequence31[0]);

	int sequence32[] = { 9,  1,  9,  2,  3,  4,  5,  9,  9,
						 40, 39, 38, 37, 36, 35, 34, 33, 32, 31 };
	int length32 = sizeof(sequence32) / sizeof(sequence32[0]);

	int subsequence3[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31 };
	int length3 = sizeof(subsequence3) / sizeof(subsequence3[0]);

	result_length = algorithm(sequence31, length31, sequence32, length32, result_subsequence);
	std::cout << "test #3: " << ((result_length == length3) ? "ok" : "FAILED") << '\n';
	std::cout << "test #3.1: "
		<< ((Common::is_equal(subsequence3, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence41[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, };
	int length41 = sizeof(sequence41) / sizeof(sequence41[0]);

	int sequence42[] = { 9,  1,  9,  2,  3,  4,  5,  9,  9,
						 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21 };
	int length42 = sizeof(sequence42) / sizeof(sequence42[0]);

	int subsequence4[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						   30, 29, 28, 27, 26, 25, 24, 23, 22, 21 };
	int length4 = sizeof(subsequence4) / sizeof(subsequence4[0]);

	result_length = algorithm(sequence41, length41, sequence42, length42, result_subsequence);
	std::cout << "test #4: " << ((result_length == length4) ? "ok" : "FAILED") << '\n';
	std::cout << "test #4.1: "
		<< ((Common::is_equal(subsequence4, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence51[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						  0,  1,  0,  0,  2,  0,  3,  0,  4,  0, 5,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length51 = sizeof(sequence51) / sizeof(sequence51[0]);

	int sequence52[] = { 9,  1,  9,  2,  3,  4,  5,  9,  9,
						 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length52 = sizeof(sequence52) / sizeof(sequence52[0]);

	int subsequence5[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						   30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						   20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length5 = sizeof(subsequence5) / sizeof(subsequence5[0]);

	//result_subsequence = new int[static_cast <unsigned> (length5)];
	result_length = algorithm(sequence51, length51, sequence52, length52, result_subsequence);
	std::cout << "test #5: " << ((result_length == length5) ? "ok" : "FAILED") << '\n';
	std::cout << "test #5.1: "
		<< ((Common::is_equal(subsequence5, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence61[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						  0,  1,  0,  0,  2,  0,  3,  0,  4,  0, 5,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
						  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
	int length61 = sizeof(sequence61) / sizeof(sequence61[0]);

	int sequence62[] = { 9,  1,  9,  2,  3,  4,  5,  9,  9,
						 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length62 = sizeof(sequence62) / sizeof(sequence62[0]);

	int subsequence6[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						   30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						   20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length6 = sizeof(subsequence6) / sizeof(subsequence6[0]);

	result_length = algorithm(sequence61, length61, sequence62, length62, result_subsequence);
	std::cout << "test #6: " << ((result_length == length6) ? "ok" : "FAILED") << '\n';
	std::cout << "test #6.1: "
		<< ((Common::is_equal(subsequence6, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence71[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						  0,  1,  0,  0,  2,  0,  3,  0,  4,  0, 5,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
						  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
	int length71 = sizeof(sequence71) / sizeof(sequence71[0]);

	int sequence72[] = { 9,  1,  9,  2,  3,  4,  5,  9,  9,
						 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length72 = sizeof(sequence72) / sizeof(sequence72[0]);

	int subsequence7[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						   30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						   20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length7 = sizeof(subsequence7) / sizeof(subsequence7[0]);

	result_length = algorithm(sequence71, length71, sequence72, length72, result_subsequence);
	std::cout << "test #7: " << ((result_length == length7) ? "ok" : "FAILED") << '\n';
	std::cout << "test #7.1: "
		<< ((Common::is_equal(subsequence7, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence81[] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
	int length81 = sizeof(sequence81) / sizeof(sequence81[0]);

	int sequence82[] = { 9,  9,  9,  9,  9,  9,  9,  9,  9,  9 };
	int length82 = sizeof(sequence82) / sizeof(sequence82[0]);

	int length8 = 0;
	int* subsequence8 = nullptr;

	result_length = algorithm(sequence81, length81, sequence82, length82, result_subsequence);
	std::cout << "test #8: " << ((result_length == length8) ? "ok" : "FAILED") << '\n';
	std::cout << "test #8.1: "
		<< ((Common::is_equal(subsequence8, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence91[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						  0,  1,  0,  0,  2,  0,  3,  0,  4,  0, 5,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
						  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
	int length91 = sizeof(sequence91) / sizeof(sequence91[0]);

	int sequence92[] = { 9,  1,  9,  2,  3,  4,  5,  9,  9,
						 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
						 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
						 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length92 = sizeof(sequence92) / sizeof(sequence92[0]);

	int subsequence9[] = { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
						   30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
						   20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	int length9 = sizeof(subsequence9) / sizeof(subsequence9[0]);

	result_length = algorithm(sequence91, length91, sequence92, length92, result_subsequence);
	std::cout << "test #9: " << ((result_length == length9) ? "ok" : "FAILED") << '\n';
	std::cout << "test #9.1: "
		<< ((Common::is_equal(subsequence9, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;
}
