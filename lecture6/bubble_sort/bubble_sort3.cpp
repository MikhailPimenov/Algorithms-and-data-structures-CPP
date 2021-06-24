#include "bubble_sort3.h"

namespace Bubble_sort3 {
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

void bubble_sort3(int* a, int length)
{
	for (int i1 = 0; i1 < length - 1; ++i1) {
		bool go_on = false;
		for (int i2 = 0; i2 < length - 1 - i1; ++i2) {
			if (a[i2] > a[i2 + 1]) {
				Bubble_sort3::swap(a[i2], a[i2 + 1]);
				go_on = true;
			}
		}
		if (!go_on) return;
	}
}
