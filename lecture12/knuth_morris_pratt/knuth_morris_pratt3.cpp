#include "knuth_morris_pratt3.h"


int knuth_morris_pratt3(const char* s, int length, const char* ss, int slength)
{
	--length;
	--slength;

	if (!length || !slength || length < slength)
		return -1;

	char* longstring = new char[slength + 1 + length];

	for (int i = 0; i < slength; ++i)
		longstring[i] = ss[i];

	longstring[slength] = '#';
	for (int i = slength + 1; i < slength + 1 + length; ++i)
		longstring[i] = s[i - slength - 1];

	int* p_array = new int[slength + 1 + length];
	p_function3(longstring, p_array, slength + 1 + length);

	int result = -1;

	for (int i = 2 * slength; i < slength + 1 + length; ++i) {
		if (p_array[i] == slength) {
			result = i - 2 * slength;
			break;
		}
	}

	delete[] p_array;
	delete[] longstring;

	return result;
}
