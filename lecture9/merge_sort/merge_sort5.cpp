#include "merge_sort5.h"

static void merge(int* a, int length, const int* a1, int length1, const int* a2, int length2) {
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

static void copy(int* destination, const int* source, int length) {
	for (int index = 0; index < length; ++index)
		destination[index] = source[index];
}

static void merge_sort_actual(int* a, int* buffer, int length) {
	if (length < 2) return;

	merge_sort_actual(a, buffer, length / 2);
	merge_sort_actual(a + length / 2, buffer + length / 2, length - length / 2);

	merge(buffer, length, a, length / 2, a + length / 2, length - length / 2);

	copy(a, buffer, length);
}

void merge_sort5(int* a, int length) {
	int* buffer = new int[length];
	merge_sort_actual(a, buffer, length);
	delete[] buffer;

}