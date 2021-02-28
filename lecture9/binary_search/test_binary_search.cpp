#include "test_binary_search.h"

void test_binary_search(bool (*algorithm)(const int*, int, int, int&, int&))
{
	std::cout << "testing_binary_search:\n";

	int array[]{ 1, 1, 1, 1, 1, 2, 2, 3, 4, 4, 4, 6, 6, 7, 7, 7, 7, 7, 8, 9 };
	int length = sizeof(array) / sizeof(array[0]);

	int resultLeft;
	int resultRight;

	int element = 0;
	int left = -1;
	int right = 0;

	bool result = false;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #1: "
		<< ((!result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 12;
	left = 19;
	right = 20;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #2: "
		<< ((!result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 1;
	left = -1;
	right = 5;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #3: "
		<< ((result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 2;
	left = 4;
	right = 7;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #4: "
		<< ((result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 3;
	left = 6;
	right = 8;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #5: "
		<< ((result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 5;
	left = 10;
	right = 11;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #6: "
		<< ((!result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 7;
	left = 12;
	right = 18;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #7: "
		<< ((result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';


	element = 8;
	left = 17;
	right = 19;
	result = algorithm(array, length, element, resultLeft, resultRight);
	std::cout << "test #8: "
		<< ((result && (resultLeft == left) && (resultRight == right)) ? "ok" : "FAILED")
		<< '\n';
}
