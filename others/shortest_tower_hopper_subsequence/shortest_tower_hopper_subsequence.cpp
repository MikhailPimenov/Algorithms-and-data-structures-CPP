#include "shortest_tower_hopper_subsequence.h"

int shortest_tower_hopper_subsequence(const int* a, int length) {
	int* f = new int[static_cast<unsigned long long>(length) + 1ull];
	f[0] = 1;

	for (int i = 1; i < length + 1; ++i) {
		int minimum = length + 1;

		for (int j = 0; j < i; ++j)
			if (a[j] + j >= i && f[j] < minimum)
				minimum = f[j];

		f[i] = minimum + 1;
	}

	int result = f[length] - 1;
	
	delete[] f;

	return result;
}