#include "bubble_sort4.h"

namespace Bubble_sort4 {
	void swap(int &a, int &b) {
		int buffer = a;
		a = b;
		b = buffer;
	}
}
void bubble_sort4(int* a, int length)
{
	for (int i = length; i >= 0; --i) {
		bool go_on = false;

		for (int j = 0; j < length - 1; ++j) {
			if (a[j] > a[j + 1]) {
				Bubble_sort4::swap(a[j], a[j + 1]);
				go_on = true;
			}
		}

		if (!go_on) break;
	}
}
