#include "longest_increasing_subsequence3.h"


int get_length_of_longest_increasing_subsequence3(const int* a, int length, int* f) {
	for (int i = 0; i < length; ++i) {
		int maximum = 0;
		for (int j = 0; j < i; ++j) {
			if (a[j] < a[i] && f[j] > maximum) {
				maximum = f[j];
			}
		}
		f[i] = maximum + 1;
	}

	int maximum = 0;
	for (int i = 0; i < length; ++i) {
		if (f[i] > maximum) {
			maximum = f[i];
		}
	}

	return maximum;
}

void reveal_longest_increasing_subsequence3(const int* a, int length, const int* f, int* s_out, int s_length) {
	int start = 0;
	int maximum = 0;
	for (int i = 0; i < length; ++i) {
		if (f[i] > maximum) {
			maximum = f[i];
			start = i;
		}
	}

	int s_index = s_length - 1;
	s_out[s_index] = a[start];
	--s_index;

	for (int i = start; i >= 0; --i) {
		if (f[i] == maximum - 1) {
			s_out[s_index] = a[i];
			--s_index;
			--maximum;
		}
		if (maximum == 1) break;
	}
}

int longest_increasing_subsequence3(const int* a, int length, int*& s_out)
{
	int* f = new int[length];
	int s_length = get_length_of_longest_increasing_subsequence3(a, length, f);

	s_out = new int[s_length];
	reveal_longest_increasing_subsequence3(a, length, f, s_out, s_length);

	delete[] f;

	return s_length;
}
