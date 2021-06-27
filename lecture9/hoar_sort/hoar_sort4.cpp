#include "hoar_sort4.h"

namespace Hoar_sort4 {
	void swap(int& x, int& y) {
		int buffer = x;
		x = y;
		y = buffer;
	}
}

void hoar_sort4(int* a, int length) {
	if (length < 2) return;

	int pivot_index = 0; // got to be random
	int pivot = a[pivot_index];

	int lower = 0;
	int greater = 0;
	for (int i = 0; i < length; ++i) {
		if (a[i] < pivot) ++lower;
		else if (a[i] > pivot) ++greater;
	}
	int equal = length - lower - greater;

	int lower_index = 0;
	int equal_index = lower;
	int greater_index = length - 1;
	while(equal_index <= greater_index){
		if (a[greater_index] > pivot) --greater_index;
		else if (a[greater_index] < pivot) {
			Hoar_sort4::swap(a[greater_index], a[lower_index]);
			++lower_index;
		}
		else {
			Hoar_sort4::swap(a[greater_index], a[equal_index]);
			++equal_index;
		}
	}

	hoar_sort4(a, lower);
	hoar_sort4(a + lower + equal, greater);
}
