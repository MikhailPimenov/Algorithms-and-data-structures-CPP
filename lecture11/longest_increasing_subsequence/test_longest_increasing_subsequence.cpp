#include "test_longest_increasing_subsequence.h"

void test_longest_increasing_subsequence(int (*algorithm) (const int*, int, int*&))
{
	std::cout << "test_longest_increasing_subsequence:\n";

	int sequence1[] = { 1, 2, 3, 4, 5 };
	int length1 = sizeof(sequence1) / sizeof(sequence1[0]);

	int subsequence1[] = { 1, 2, 3, 4, 5 };
	int sub_length1 = sizeof(subsequence1) / sizeof(subsequence1[0]);

	int* result_subsequence = nullptr;// = new int[static_cast <unsigned> (sub_length1)];
	int result_length = 0;

	result_length = algorithm(sequence1, length1, result_subsequence);
	std::cout << "test #1: " << ((result_length == sub_length1) ? "ok" : "FAILED") << '\n';
	std::cout << "test #1.1: "
		<< ((Common::is_equal(subsequence1, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';

	delete[] result_subsequence;


	int sequence2[] = { 1, 9, 2, 8, 3, 7, 4, 6, 5, 6 };
	int length2 = sizeof(sequence2) / sizeof(sequence2[0]);

	int subsequence2[] = { 1, 2, 3, 4, 5, 6 };
	int sub_length2 = sizeof(subsequence2) / sizeof(subsequence2[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length2)];
	result_length = 0;

	result_length = algorithm(sequence2, length2, result_subsequence);
	std::cout << "test #2: " << ((result_length == sub_length2) ? "ok" : "FAILED") << '\n';
	std::cout << "test #2.1: "
		<< ((Common::is_equal(subsequence2, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence3[] = { 1, 9, 2, 9, 3, 9, 4, 9 };
	int length3 = sizeof(sequence3) / sizeof(sequence3[0]);

	int subsequence3[] = { 1, 2, 3, 4, 9 };
	int sub_length3 = sizeof(subsequence3) / sizeof(subsequence3[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length3)];
	result_length = 0;

	result_length = algorithm(sequence3, length3, result_subsequence);
	std::cout << "test #3: " << ((result_length == sub_length3) ? "ok" : "FAILED") << '\n';
	std::cout << "test #3.1: "
		<< ((Common::is_equal(subsequence3, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence4[] = { 4, 3, 1, 2 };
	int length4 = sizeof(sequence4) / sizeof(sequence4[0]);

	int subsequence4[] = { 1, 2 };
	int sub_length4 = sizeof(subsequence4) / sizeof(subsequence4[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length4)];
	result_length = 0;

	result_length = algorithm(sequence4, length4, result_subsequence);
	std::cout << "test #4: " << ((result_length == sub_length4) ? "ok" : "FAILED") << '\n';
	std::cout << "test #4.1: "
		<< ((Common::is_equal(subsequence4, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence5[] = { 4, 1, 2, 0 };
	int length5 = sizeof(sequence5) / sizeof(sequence5[0]);

	int subsequence5[] = { 1, 2 };
	int sub_length5 = sizeof(subsequence5) / sizeof(subsequence5[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length5)];
	result_length = 0;

	result_length = algorithm(sequence5, length5, result_subsequence);
	std::cout << "test #5: " << ((result_length == sub_length5) ? "ok" : "FAILED") << '\n';
	std::cout << "test #5.1: "
		<< ((Common::is_equal(subsequence5, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence6[] = { 9, 8, 7, 1, 6, 2, 3 };
	int length6 = sizeof(sequence6) / sizeof(sequence6[0]);

	int subsequence6[] = { 1, 2, 3 };
	int sub_length6 = sizeof(subsequence6) / sizeof(subsequence6[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length6)];
	result_length = 0;

	result_length = algorithm(sequence6, length6, result_subsequence);
	std::cout << "test #6: " << ((result_length == sub_length6) ? "ok" : "FAILED") << '\n';
	std::cout << "test #6.1: "
		<< ((Common::is_equal(subsequence6, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence7[] = { 0, 0, 1, 0, 0, 2, 0, 0, 3, 0, 0, 4, 0, 0, 5 };
	int length7 = sizeof(sequence7) / sizeof(sequence7[0]);

	int subsequence7[] = { 0, 1, 2, 3, 4, 5 };
	int sub_length7 = sizeof(subsequence7) / sizeof(subsequence7[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length7)];
	result_length = 0;

	result_length = algorithm(sequence7, length7, result_subsequence);
	std::cout << "test #7: " << ((result_length == sub_length7) ? "ok" : "FAILED") << '\n';
	std::cout << "test #7.1: "
		<< ((Common::is_equal(subsequence7, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence8[] = { 0, 0, 1, 0, 0, 2, 0, 0, 3, 2, 2, 4, 0, 0, 5 };
	int length8 = sizeof(sequence8) / sizeof(sequence8[0]);

	int subsequence8[] = { 0, 1, 2, 3, 4, 5 };
	int sub_length8 = sizeof(subsequence8) / sizeof(subsequence8[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length8)];
	result_length = 0;

	result_length = algorithm(sequence8, length8, result_subsequence);
	std::cout << "test #8: " << ((result_length == sub_length8) ? "ok" : "FAILED") << '\n';
	std::cout << "test #8.1: "
		<< ((Common::is_equal(subsequence8, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence9[] = { 0, 0, 1, 0, 9, 2, 9, 9, 3, 2, 2, 4, 0, 0, 5 };
	int length9 = sizeof(sequence9) / sizeof(sequence9[0]);

	int subsequence9[] = { 0, 1, 2, 3, 4, 5 };
	int sub_length9 = sizeof(subsequence9) / sizeof(subsequence9[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length9)];
	result_length = 0;

	result_length = algorithm(sequence9, length9, result_subsequence);
	std::cout << "test #9: " << ((result_length == sub_length9) ? "ok" : "FAILED") << '\n';
	std::cout << "test #9.1: "
		<< ((Common::is_equal(subsequence9, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence10[] = { 4, 1, 2, 3, 0, 1 };
	int length10 = sizeof(sequence10) / sizeof(sequence10[0]);

	int subsequence10[] = { 1, 2, 3 };
	int sub_length10 = sizeof(subsequence10) / sizeof(subsequence10[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length10)];
	result_length = 0;

	result_length = algorithm(sequence10, length10, result_subsequence);
	std::cout << "test #10: " << ((result_length == sub_length10) ? "ok" : "FAILED") << '\n';
	std::cout << "test #10.1: "
		<< ((Common::is_equal(subsequence10, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence11[] = { 4, 1, 2, 9, 3, 4, 5, 0, 1 };
	int length11 = sizeof(sequence11) / sizeof(sequence11[0]);

	int subsequence11[] = { 1, 2, 3, 4, 5 };
	int sub_length11 = sizeof(subsequence11) / sizeof(subsequence11[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length11)];
	result_length = 0;

	result_length = algorithm(sequence11, length11, result_subsequence);
	std::cout << "test #11: " << ((result_length == sub_length11) ? "ok" : "FAILED") << '\n';
	std::cout << "test #11.1: "
		<< ((Common::is_equal(subsequence11, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


	int sequence12[] = { 4, 5, 1, 2, 0, 3, 3, 3, 0, 0, 1 };
	int length12 = sizeof(sequence12) / sizeof(sequence12[0]);

	int subsequence12[] = { 1, 2, 3 };
	int sub_length12 = sizeof(subsequence12) / sizeof(subsequence12[0]);

	//result_subsequence = new int[static_cast <unsigned> (sub_length12)];
	result_length = 0;

	result_length = algorithm(sequence12, length12, result_subsequence);
	std::cout << "test #12: " << ((result_length == sub_length12) ? "ok" : "FAILED") << '\n';
	std::cout << "test #12.1: "
		<< ((Common::is_equal(subsequence12, result_subsequence, result_length)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result_subsequence;


}
