#include "insertion_sort5.h"

static void swap(int& a, int& b) {
	const auto temporary = a;
	a = b;
	b = temporary;
}

void insertion_sort5(int* a, int length) {
	for (int index_to_insert = 1; index_to_insert < length; ++index_to_insert) {
		for (int index_to_compare = index_to_insert - 1; index_to_compare >= 0; --index_to_compare) {
			if (a[index_to_compare] > a[index_to_compare + 1]) {
				swap(a[index_to_compare], a[index_to_compare + 1]);
			}
		}
	}
}