#include "hoar_sort5.h"

static void swap(int& a, int& b) {
	const int temporary = a;
	a = b;
	b = temporary;
}

void hoar_sort5(int* a, int length) {
	if (length < 2) return;

	const int pivot_index = 0; // got to be random
	const int pivot = a[pivot_index];

	int lower = 0;
	int greater = 0;
	for (int index = 0; index < length; ++index) {
		if (a[index] < pivot) ++lower;
		else if (a[index] > pivot) ++greater;
	}
	const int equal = length - lower - greater;


	int lower_index = 0;
	int greater_index = length - 1;
	int equal_index = lower;

	while (greater_index >= equal_index) {
		if (a[greater_index] < pivot) {
			swap(a[greater_index], a[lower_index]);
			++lower_index;
		}
		else if (a[greater_index] == pivot) {
			swap(a[greater_index], a[equal_index]);
			++equal_index;
		}
		else --greater_index;
	}

	hoar_sort5(a, lower);
	hoar_sort5(a + lower + equal, greater);
}