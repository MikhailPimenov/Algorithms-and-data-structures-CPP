#include "longest_common_subsequence3.h"

namespace Longest_common_subsequence3 {
	int maximum(int a, int b) {
		return a >= b ? a : b;
	}
}

int get_length_of_longest_common_subsequence3(const int* a1, int length1, const int* a2, int length2, int** ff)
{
	for (int i = 1; i < length2 + 1; ++i)
		for (int j = 1; j < length1 + 1; ++j)
			if (a1[j - 1] == a2[i - 1]) ff[i][j] = ff[i - 1][j - 1] + 1;
			else ff[i][j] = Longest_common_subsequence3::maximum(ff[i - 1][j], ff[i][j - 1]);

	return ff[length2][length1];
}

void reveal_longest_common_subsequence3(const int* a1, int length1, const int* a2, int length2, const int** ff, int* s_out, int length)
{
	int i = length2;
	int j = length1;
	int s_index = length - 1;

	while (i && j) {
		if (ff[i - 1][j] == ff[i][j - 1]) {
			if (ff[i - 1][j - 1] < ff[i][j]) {
				s_out[s_index] = a1[j - 1];
				--s_index;
			}
			--i;
			--j;
		}
		else {
			if (ff[i - 1][j] > ff[i][j - 1]) --i;
			else --j;
		}
	}
}
int longest_common_subsequence3(const int* a1, int length1, const int* a2, int length2, int*& s_out)
{
	int* f_long = new int[(length1 + 1) * (length2 + 1)];
	int** ff = new int* [length2 + 1];

	for (int i = 0; i < length2 + 1; ++i)
		ff[i] = f_long + i * (length1 + 1);
	for (int i = 0; i < length2 + 1; ++i)
		ff[i][0] = 0;
	for (int j = 0; j < length1 + 1; ++j)
		ff[0][j] = 0;

	int length = get_length_of_longest_common_subsequence3(a1, length1, a2, length2, ff);

	s_out = new int[length];
	reveal_longest_common_subsequence3(a1, length1, a2, length2, const_cast<const int**>(ff), s_out, length);

	delete[] ff;
	delete[] f_long;

	return length;
}
