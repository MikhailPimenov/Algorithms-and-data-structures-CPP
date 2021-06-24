#include "merge_sort3.h"

namespace Merge_sort3 {
	void copy(int* destination, int length, const int* source) {
		for (int i = 0; i < length; ++i)
			destination[i] = source[i];
	}
	void merge(int* a, int l, const int* a1, int l1, const int* a2, int l2) {
		assert(l == l1 + l2);

		int i = 0;
		int i1 = 0;
		int i2 = 0;

		while (i1 < l1 && i2 < l2) {
			if (a1[i1] <= a2[i2]) {
				a[i] = a1[i1];
				++i1;
			}
			else {
				a[i] = a2[i2];
				++i2;
			}
			++i;
		}

		while (i1 < l1) {
			a[i] = a1[i1];
			++i1;
			++i;
		}
		while (i2 < l2) {
			a[i] = a2[i2];
			++i2;
			++i;
		}
	}
	void merge_sort_recursive(int* a, int length, int* b) {
		if (length < 2) return;

		merge_sort_recursive(a, length / 2, b);
		merge_sort_recursive(a + length / 2, length - length / 2, b);

		merge(b, length, a, length / 2, a + length / 2, length - length / 2);
		copy(a, length, b);
	}
}

void merge_sort3(int* a, int length)
{
	int* b = new int[length];
	Merge_sort3::merge_sort_recursive(a, length, b);
	delete[] b;
}
