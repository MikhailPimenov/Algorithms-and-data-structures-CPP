#include "test_p_function.h"

void test_p_function(void (*algorithm) (const char*, int*, int))
{
	std::cout << "test_p_function:\n";

	const char* cString1 = "abababa";
	int length1 = Common::length(cString1) - 1;
	int* result = new int[static_cast <unsigned> (length1)];
	algorithm(cString1, result, length1);
	int p_array1[]{ 0, 0, 1, 2, 3, 4, 5 };

	std::cout << "test #1: "
		<< ((Common::is_equal(p_array1, result, length1)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result;


	const char* cString2 = "acdabcdabacd";
	int length2 = Common::length(cString2) - 1;
	result = new int[static_cast <unsigned> (length2)];
	algorithm(cString2, result, length2);
	int p_array2[]{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 2, 3 };

	std::cout << "test #2: "
		<< ((Common::is_equal(p_array2, result, length2)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result;


	const char* cString3 = "alalcda";
	int length3 = Common::length(cString3) - 1;
	result = new int[static_cast <unsigned> (length3)];
	algorithm(cString3, result, length3);
	int p_array3[]{ 0, 0, 1, 2, 0, 0, 1 };

	std::cout << "test #3: "
		<< ((Common::is_equal(p_array3, result, length3)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result;


	const char* cString4 = "akeakea";
	int length4 = Common::length(cString4) - 1;
	result = new int[static_cast <unsigned> (length4)];
	algorithm(cString4, result, length4);
	int p_array4[]{ 0, 0, 0, 1, 2, 3, 4 };

	std::cout << "test #4: "
		<< ((Common::is_equal(p_array4, result, length4)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result;


	const char* cString5 = "pig is big#pig pig pig is very big pig pig is big";
	int length5 = Common::length(cString5) - 1;
	result = new int[static_cast <unsigned> (length5)];
	algorithm(cString5, result, length5);
	int p_array5[]{
		0,0,0,0,0,0,0,
		0,0,0,0,1,2,3,
		4,1,2,3,4,1,2,
		3,4,5,6,7,0,0,
		0,0,0,0,0,0,0,
		1,2,3,4,1,2,3,
		4,5,6,7,8,9,10
	};

	std::cout << "test #5: "
		<< ((Common::is_equal(p_array5, result, length5)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result;


	const char* cString6 = "abcabababcabck";
	int length6 = Common::length(cString6) - 1;
	result = new int[static_cast <unsigned> (length6)];
	algorithm(cString6, result, length6);
	int p_array6[]{ 0,0,0,1,2,1,2,1,2,3,4,5,3,0 };

	std::cout << "test #6: "
		<< ((Common::is_equal(p_array6, result, length6)) ? "ok" : "FAILED")
		<< '\n';
	delete[] result;

}
