#include "hoar_sort3.h"

namespace Hoar_sort3 {
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

void hoar_sort3(int* a, int length)
{
	if (length < 1) return;

	int pivot_index = 0; //got to be random
	int pivot = a[pivot_index];

	int lower = 0;
	int greater = 0;
	for (int i = 0; i < length; ++i)
		if (a[i] < pivot) ++lower;
		else if (a[i] > pivot) ++greater;

	int equal = length - lower - greater;

	int lower_index = 0;
	int greater_index = length - 1;
	int equal_index = lower;

	while (greater_index >= equal_index) {
		if (a[greater_index] < pivot) {
			Hoar_sort3::swap(a[greater_index], a[lower_index]);
			++lower_index;
		}
		else if (a[greater_index] == pivot) {
			Hoar_sort3::swap(a[greater_index], a[equal_index]);
			++equal_index;
		}
		else --greater_index;
	}

	hoar_sort3(a, lower);
	hoar_sort3(a + lower + equal, greater);
}
