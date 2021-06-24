#include "select_sort3.h"

namespace Select_sort3 {
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

void select_sort3(int* a, int length)
{
	for (int i = 0; i < length - 1; ++i) {
		int m = 0;
		for (int j = 1; j < length - i; ++j) {
			if (a[j] > a[m]) m = j;
		}
		Select_sort3::swap(a[length - 1 - i], a[m]);
	}
}
