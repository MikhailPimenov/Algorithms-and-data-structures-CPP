#include "bubble_sort5.h"
// 5 1 3 2 4

static void swap(int& a, int& b) {
	const auto temporary = a;
	a = b;
	b = temporary;
}

void bubble_sort5(int* a, int length) {
	for (int i = 0; i < length - 1; ++i) {
		bool stop = true;

		for (int j = 0; j < length - i - 1; ++j) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				stop = false;
			}
		}

		if (stop) return;
	}
}