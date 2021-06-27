#include "merge_sort4.h"

namespace Merge_sort4 {
	void copy(int* destination, int* source, int length) {
		for (int i = 0; i < length; ++i)
			destination[i] = source[i];
	}

	void merge(int* a, int length, int* a1, int length1, int *a2, int length2) {
		int index = 0;
		int index1 = 0;
		int index2 = 0;

		while (index1 < length1 && index2 < length2) {
			if (a1[index1] <= a2[index2]) {
				a[index] = a1[index1];
				++index1;
			}
			else {
				a[index] = a2[index2];
				++index2;
			}
			++index;
		}

		while (index1 < length1) {
			a[index] = a1[index1];
			++index1;
			++index;
		}
		while (index2 < length2) {
			a[index] = a2[index2];
			++index2;
			++index;
		}
	}

	void merge_sort_recursive(int* a, int length, int* buffer) {
		if (length < 2) return;

		merge_sort_recursive(a, length / 2, buffer);
		merge_sort_recursive(a + length / 2, length - length / 2, buffer + length / 2);

		merge(buffer, length, a, length / 2, a + length / 2, length - length / 2);

		copy(a, buffer, length);
	}
}

void merge_sort4(int* a, int length) {
	int* buffer = new int[length];

	Merge_sort4::merge_sort_recursive(a, length, buffer);

	delete[] buffer;
}
