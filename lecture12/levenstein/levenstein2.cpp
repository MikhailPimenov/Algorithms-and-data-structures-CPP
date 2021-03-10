#include "levenstein2.h"

namespace Levenstein2 {
	int get_length(const char* array)
	{
		int length = 0;

		while (array[length] != '\0')
			++length;
		++length;

		return length;
	}
	int minimum(int a, int b, int c)
	{
		return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
	}
}

int levenstein2(const char* array1, int length1, const char* array2, int length2)
{
	int* f_long = new int[(length1 + 1) * (length2 + 1)];
	int** f = new int* [length2 + 1];
	for (int i = 0; i < length2 + 1; ++i)
		f[i] = f_long + (length1 + 1) * i;

	for (int i = 0; i < length2 + 1; ++i)
		f[i][0] = i;

	for (int j = 0; j < length1 + 1; ++j)
		f[0][j] = j;

	for (int i = 1; i < length2 + 1; ++i)
		for (int j = 1; j < length1 + 1; ++j)
			if (array1[j - 1] == array2[i - 1])
				f[i][j] = f[i - 1][j - 1];
			else
				f[i][j] = 1 + Levenstein2::minimum(f[i - 1][j], f[i][j - 1], f[i - 1][j - 1]);

	int result = f[length2][length1];
	delete[] f;
	delete[] f_long;

	return result;
}

int levenstein_adapted2(const char* array1, const char* array2)
{
	int length1 = Levenstein2::get_length(array1);
	int length2 = Levenstein2::get_length(array2);

	int length = levenstein2(array1, length1, array2, length2);
	return length;
}
