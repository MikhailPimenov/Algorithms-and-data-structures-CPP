#include "selection_sort5.h"

static void swap(int& a, int& b) {
	const auto temporary = a;
	a = b;
	b = temporary;
}

void selection_sort5(int* a, int length) {
	for (int index_to_replace = 0; index_to_replace < length - 1; ++index_to_replace) {
		int index_of_minimum = index_to_replace;

		for (int search_index = index_to_replace; search_index < length; ++search_index) {
			if (a[search_index] < a[index_of_minimum])
				index_of_minimum = search_index;
		}
		swap(a[index_to_replace], a[index_of_minimum]);
	}
}