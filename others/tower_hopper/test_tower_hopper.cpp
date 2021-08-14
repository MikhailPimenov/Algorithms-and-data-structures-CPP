#include "test_tower_hopper.h"

void test_tower_hopper(bool (*algorithm)(const int*, int)){
	std::cout << "test_tower_hopper:\n";

	bool expected = true;
	bool actual = true;

	const int array1[] = { 4,2,0,0,2,0, };
	const int length1 = sizeof(array1) / sizeof(array1[0]);
	
	expected = true;
	actual = algorithm(array1, length1);

	std::cout << "test # 1: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array2[] = { 4,2,0,0,2,0,0,0,0,0,0,};
	const int length2 = sizeof(array2) / sizeof(array2[0]);

	expected = false;
	actual = algorithm(array2, length2);

	std::cout << "test # 2: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array3[] = { 0,9,9, };
	const int length3 = sizeof(array3) / sizeof(array3[0]);

	expected = false;
	actual = algorithm(array3, length3);

	std::cout << "test # 3: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array4[] = { 4,0,0,0,0,2,2,5 };
	const int length4 = sizeof(array4) / sizeof(array4[0]);

	expected = false;
	actual = algorithm(array4, length4);

	std::cout << "test # 4: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array5[] = { 1,1,1,1,1,1, };
	const int length5 = sizeof(array5) / sizeof(array5[0]);

	expected = true;
	actual = algorithm(array5, length5);

	std::cout << "test # 5: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array6[] = { 0,0,0, };
	const int length6 = sizeof(array6) / sizeof(array6[0]);

	expected = false;
	actual = algorithm(array6, length6);

	std::cout << "test # 6: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array7[] = { 2,2,0,2,4,8,0,0,0,0,0 };
	const int length7 = sizeof(array7) / sizeof(array7[0]);

	expected = true;
	actual = algorithm(array7, length7);

	std::cout << "test # 7: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array8[] = { 3, 0, 1, 2, 3, 0, 0, 1 };
	const int length8 = sizeof(array8) / sizeof(array8[0]);

	expected = true;
	actual = algorithm(array8, length8);

	std::cout << "test # 8: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array9[] = { 1, };
	const int length9 = sizeof(array9) / sizeof(array9[0]);

	expected = true;
	actual = algorithm(array9, length9);

	std::cout << "test # 9: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array10[] = { 5, };
	const int length10 = sizeof(array10) / sizeof(array10[0]);

	expected = true;
	actual = algorithm(array10, length10);

	std::cout << "test #10: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int *array11 = nullptr;
	const int length11 = 0;

	expected = true;
	actual = algorithm(array11, length11);

	std::cout << "test #11: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array12[] = { -5, };
	const int length12 = sizeof(array12) / sizeof(array12[0]);

	expected = false;
	actual = algorithm(array12, length12);

	std::cout << "test #12: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array13[] = { -5, -6, -7, -7, 0};
	const int length13 = sizeof(array13) / sizeof(array13[0]);

	expected = false;
	actual = algorithm(array13, length13);

	std::cout << "test #13: " << (actual == expected ? "ok" : "FALIED") << '\n';


	const int array14[] = { 2, -6, 2, -7, 1 };
	const int length14 = sizeof(array14) / sizeof(array14[0]);

	expected = true;
	actual = algorithm(array14, length14);

	std::cout << "test #14: " << (actual == expected ? "ok" : "FALIED") << '\n';

}