#include "test_find_substring.h"

void test_find_substring(int (*algorithm) (const char*, int, const char*, int))
{
	std::cout << "test_find_substring:\n";

	const char* s11 = "This pig is very big!";
	const char* s12 = "big";
	int answer = 17;
	int result = algorithm(s11, Common::length(s11), s12, Common::length(s12));

	std::cout << "test #1: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s21 = "I forgot green bag on the sofa.";
	const char* s22 = "green";
	answer = 9;
	result = algorithm(s21, Common::length(s21), s22, Common::length(s22));

	std::cout << "test #2: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s31 = "I used to pump my shoulders before bench press";
	const char* s32 = "press";
	answer = 41;
	result = algorithm(s31, Common::length(s31), s32, Common::length(s32));

	std::cout << "test #3: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s41 = "This weather gets me down.";
	const char* s42 = "dog";
	answer = -1;
	result = algorithm(s41, Common::length(s41), s42, Common::length(s42));

	std::cout << "test #4: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s51 = "Table is black.";
	const char* s52 = "Table";
	answer = 0;
	result = algorithm(s51, Common::length(s51), s52, Common::length(s52));

	std::cout << "test #5: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s61 = "Flower grew up on my garden.";
	const char* s62 = "on";
	answer = 15;
	result = algorithm(s61, Common::length(s61), s62, Common::length(s62));

	std::cout << "test #6: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s71 = "";
	const char* s72 = "";
	answer = -1;
	result = algorithm(s71, Common::length(s71), s72, Common::length(s72));

	std::cout << "test #7: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s81 = "Notreadablestatementnotreadablestatement";
	const char* s82 = "dab";
	answer = 6;
	result = algorithm(s81, Common::length(s81), s82, Common::length(s82));

	std::cout << "test #8: " << ((answer == result) ? "ok" : "FAILED") << '\n';


	const char* s91 = "pig pig pig is very big pig pig is big";
	const char* s92 = "pig is big";
	answer = 28;
	result = algorithm(s91, Common::length(s91), s92, Common::length(s92));

	std::cout << "test #9: " << ((answer == result) ? "ok" : "FAILED") << '\n';
}
