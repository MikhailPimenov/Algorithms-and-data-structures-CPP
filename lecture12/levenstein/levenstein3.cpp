#include "levenstein3.h"
namespace Levenstein3 {
	int get_length(const char* s) {
		int length = 0;
		while (s[length] != '\0')
			++length;
		++length;

		return length;
	}

	int min(int a, int b, int c) {
		int m = a < b ? a : b;
		return m < c ? m : c;
	}
}
int levenstein3(const char* s1, const char* s2)
{
	int length1 = Levenstein3::get_length(s1) - 1;
	int length2 = Levenstein3::get_length(s2) - 1;

	int* f_long = new int[(length1 + 1) * (length2 + 1)];
	int** ff = new int* [length2 + 1];

	for (int i = 0; i < length2 + 1; ++i)
		ff[i] = f_long + i * (length1 + 1);

	for (int i = 0; i < length2 + 1; ++i)
		ff[i][0] = i;
	for (int j = 0; j < length1 + 1; ++j)
		ff[0][j] = j;

	for (int i = 1; i < length2 + 1; ++i) {
		for (int j = 1; j < length1 + 1; ++j) {
			if (s1[j - 1] == s2[i - 1]) ff[i][j] = ff[i - 1][j - 1];
			else ff[i][j] = 1 + Levenstein3::min(ff[i - 1][j - 1], ff[i - 1][j], ff[i][j - 1]);
		}
	}
	int result = ff[length2][length1];
	delete[] ff;
	delete[] f_long;

	return result;
}
