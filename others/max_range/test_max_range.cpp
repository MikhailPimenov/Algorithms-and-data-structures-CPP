#include "test_max_range.h"

void test_max_range(void(*algorithm)(const int*, int, int&, int&)) {
	std::cout << "test_max_range:\n";

	int actual_left = 0;
	int actual_right = 0;
	int expected_left = 0;
	int expected_right = 0;

	
	const int array0[] = { -5, -5, 4, 3, };
	const int length0 = sizeof(array0) / sizeof(array0[0]);

	expected_left = 3;
	expected_right = 4;

	algorithm(array0, length0, actual_left, actual_right);
	
	std::cout << "test # 1: "
		<< ((actual_left == expected_left &&
			 actual_right == expected_right) ? "ok" : "FAILED") 
		<< '\n';


	const int array1[] = { -5, 4, 3, -5, 2 };
	const int length1 = sizeof(array1) / sizeof(array1[0]);

	expected_left = 2;
	expected_right = 4;

	algorithm(array1, length1, actual_left, actual_right);

	std::cout << "test # 2: "
		<< ((actual_left == expected_left &&
			actual_right == expected_right) ? "ok" : "FAILED")
		<< '\n';


	const int array2[] = {-10,-2, 6, 7, 8, 9, -11, -13, 5, -5, 4, 3, -5, 2, 0,-3,-4,-5,-6,-7,-8,-9, };
	const int length2 = sizeof(array2) / sizeof(array2[0]);

	expected_left = -11;
	expected_right = -2;

	algorithm(array2, length2, actual_left, actual_right);

	std::cout << "test # 3: "
		<< ((actual_left == expected_left &&
			actual_right == expected_right) ? "ok" : "FAILED")
		<< '\n';


	const int array3[] = { 5 };
	const int length3 = sizeof(array3) / sizeof(array3[0]);

	expected_left = 5;
	expected_right = 5;

	algorithm(array3, length3, actual_left, actual_right);

	std::cout << "test # 4: "
		<< ((actual_left == expected_left &&
			actual_right == expected_right) ? "ok" : "FAILED")
		<< '\n';


	const int array4[] = { 5, -6, 9 };
	const int length4 = sizeof(array4) / sizeof(array4[0]);

	algorithm(array4, length4, actual_left, actual_right);

	expected_left = -6;
	expected_right = -6;
	bool alternative_answer41 = (actual_left == expected_left && actual_right == expected_right);
	
	expected_left = 5;
	expected_right = 5;
	bool alternative_answer42 = (actual_left == expected_left && actual_right == expected_right);

	expected_left = 9;
	expected_right = 9;
	bool alternative_answer43 = (actual_left == expected_left && actual_right == expected_right);


	std::cout << "test # 5: "
		<< ((alternative_answer41||
			 alternative_answer42||
			 alternative_answer43) ? "ok" : "FAILED")
		<< '\n';


	const int array5[] = { 5, 6, -2, -3, 9 };
	const int length5 = sizeof(array5) / sizeof(array5[0]);

	algorithm(array5, length5, actual_left, actual_right);
	
	expected_left = -3;
	expected_right = -2;
	bool alternative_answer51 = (actual_left == expected_left && actual_right == expected_right);

	expected_left = 5;
	expected_right = 6;
	bool alternative_answer52 = (actual_left == expected_left && actual_right == expected_right);


	std::cout << "test # 6: "
		<< ((alternative_answer51 ||
			 alternative_answer52) ? "ok" : "FAILED")
		<< '\n';
	

	const int array6[] = { 
		-1, 19, -1, 19, -1, 18,
		-1, 17, -1, 16, -1, 15,
		-1, 30, -1, 31, -1, 32,
		-1, 33, -1, 34, -1, 35,
		-1, 36, -1, 37, -1, 38,
		-1, 39, -1, 40, -1, 41,
	};
	const int length6 = sizeof(array6) / sizeof(array6[0]);

	expected_left = 30;
	expected_right = 41;

	algorithm(array6, length6, actual_left, actual_right);

	std::cout << "test # 7: "
		<< ((actual_left == expected_left &&
			actual_right == expected_right) ? "ok" : "FAILED")
		<< '\n';
}