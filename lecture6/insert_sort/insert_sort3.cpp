#include "insert_sort3.h"

namespace Insert_sort3 {
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
}


void insert_sort3(int* a, int length)
{
	for (int i = 1; i < length; ++i) {
		int k = i;
		for (int j = i - 1; j >= 0; --j) {
			if (a[j] > a[k]) {
				Insert_sort3::swap(a[j], a[k]);
				k = j;
			}
		}
	}
}
