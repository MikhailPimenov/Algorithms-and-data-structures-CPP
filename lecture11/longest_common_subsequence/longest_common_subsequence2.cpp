#include "longest_common_subsequence2.h"

namespace Longest_common_subsequence2 {
	int get_length_of_longest_common_subsequence2(const int* array1, int length1, const int* array2, int length2, int** f)
	{
		for (int i = 1; i < length2 + 1; ++i)
			for (int j = 1; j < length1 + 1; ++j)
				if (array1[j - 1] == array2[i - 1])
					f[i][j] = f[i - 1][j - 1] + 1;
				else
					f[i][j] = ((f[i - 1][j] > f[i][j - 1]) ? f[i - 1][j] : f[i][j - 1]);
		return f[length2][length1];
	}
}


int longest_common_subsequence2(const int* array1, int length1, const int* array2, int length2, int*& array_out)
{
	int* f_long = new int[(length1 + 1) * (length2 + 1)];
	int** f = new int* [length2 + 1];

	for (int i = 0; i < length2 + 1; ++i)
		f[i] = f_long + (length1 + 1) * i;

	for (int i = 0; i < length2 + 1; ++i)
		f[i][0] = 0;
	for (int j = 0; j < length1 + 1; ++j)
		f[0][j] = 0;

	int length = Longest_common_subsequence2::get_length_of_longest_common_subsequence2(
		array1, length1, array2, length2, f
	);

	if (length == 0)
	{
		delete[] f;
		delete[] f_long;
		array_out = nullptr;
		return 0;
	}

	array_out = new int[length];
	int k = length;
	int i = length2;
	int j = length1;

	while (i > 0 && j > 0)
	{
		if (f[i - 1][j] == f[i][j - 1]) {
			if (f[i - 1][j - 1] < f[i][j]) {
				array_out[k - 1] = array1[j - 1];
				--k;
			}
			--i;
			--j;
		}
		else if (f[i - 1][j] > f[i][j - 1]) {
			--i;
		}
		else {
			--j;
		}
	}

	delete[] f;
	delete[] f_long;

	return length;
}


