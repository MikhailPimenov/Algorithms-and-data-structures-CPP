#include "test_shortest_tower_hopper_subsequence.h"

void test_shortest_tower_hopper_subsequence(int(*algorithm)(const int*, int)) {
	std::cout << "test_shortest_tower_hopper_subsequence:\n";

	int expected = 0;
	int actual = 0;

	const int array1[] = { 4,2,0,0,2,0, };
	const int length1 = sizeof(array1) / sizeof(array1[0]);

	expected = 2;
	actual = algorithm(array1, length1);

	std::cout << "test # 1: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array2[] = { 1,1,1, };
	const int length2 = sizeof(array2) / sizeof(array2[0]);

	expected = 3;
	actual = algorithm(array2, length2);

	std::cout << "test # 2: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array3[] = { 9,1,1,1 };
	const int length3 = sizeof(array3) / sizeof(array3[0]);

	expected = 1;
	actual = algorithm(array3, length3);

	std::cout << "test # 3: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array4[] = { 9,1,1,1,9,1,1,1,1,1,1,1, };
	const int length4 = sizeof(array4) / sizeof(array4[0]);

	expected = 2;
	actual = algorithm(array4, length4);

	std::cout << "test # 4: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array5[] = { 5,1,1,1,2,0, };
	const int length5 = sizeof(array5) / sizeof(array5[0]);

	expected = 2;
	actual = algorithm(array5, length5);

	std::cout << "test # 5: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array6[] = { 5,1,1,1,2,0,1 };
	const int length6 = sizeof(array6) / sizeof(array6[0]);

	expected = 3;
	actual = algorithm(array6, length6);

	std::cout << "test # 6: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array7[] = { 9,1,1,1,2,0,1 };
	const int length7 = sizeof(array7) / sizeof(array7[0]);

	expected = 1;
	actual = algorithm(array7, length7);

	std::cout << "test # 7: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array8[] = { 0,0,0, };
	const int length8 = sizeof(array8) / sizeof(array8[0]);

	expected = length8 + 1;
	actual = algorithm(array8, length8);

	std::cout << "test # 8: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array9[] = { 1,2,1,1,9,2,2,9,1,1,2,0,1, };
	const int length9 = sizeof(array9) / sizeof(array9[0]);

	expected = 4;
	actual = algorithm(array9, length9);

	std::cout << "test # 9: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array10[] = { 1,2,1,1,9,2,2,9,1,1,2,0,1,1,1,1, };
	const int length10 = sizeof(array10) / sizeof(array10[0]);

	expected = 5;
	actual = algorithm(array10, length10);

	std::cout << "test #10: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array11[] = { 1, };
	const int length11 = sizeof(array11) / sizeof(array11[0]);

	expected = 1;
	actual = algorithm(array11, length11);

	std::cout << "test #11: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int *array12 = nullptr;
	const int length12 = 0;

	expected = 0;
	actual = algorithm(array12, length12);

	std::cout << "test #12: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array13[] = { 0, };
	const int length13 = sizeof(array13) / sizeof(array13[0]);

	expected = length13 + 1;
	actual = algorithm(array13, length13);

	std::cout << "test #13: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array14[] = { 1,2,1,1,9,2,2,9,1,1,2,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0, };
	const int length14 = sizeof(array14) / sizeof(array14[0]);

	expected = length14 + 1;
	actual = algorithm(array14, length14);

	std::cout << "test #14: " << (actual == expected ? "ok" : "FALIED") << '\n';

}