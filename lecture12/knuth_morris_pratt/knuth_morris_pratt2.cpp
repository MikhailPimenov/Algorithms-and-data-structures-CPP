#include "knuth_morris_pratt2.h"



int knuth_morris_pratt2(const char* string, int length, const char* substring, int sublength)
{
	if (sublength < 2)
		return -1;

	char* superstring = new char[length + sublength - 1];

	for (int i = 0; i < sublength - 1; ++i)
		superstring[i] = substring[i];
	superstring[sublength - 1] = '#';
	for (int i = 0; i < length - 1; ++i)
		superstring[sublength + i] = string[i];

	int* p_array = new int[length + sublength - 1];
	p_function2(superstring, p_array, length + sublength - 1);

	int result = -1;
	for (int i = (sublength - 1) * 2; i < length + sublength - 1; ++i) {
		if (p_array[i] == sublength - 1) {
			result = i - (sublength - 1) * 2;
			break;
		}
	}

	delete[] p_array;
	delete[] superstring;
	return result;
}
