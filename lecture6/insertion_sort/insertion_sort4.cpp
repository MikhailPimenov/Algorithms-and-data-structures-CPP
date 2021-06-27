#include "insertion_sort4.h"

namespace Insertion_sort4 {
	void swap(int& a, int& b) {
		int buffer = a;
		a = b;
		b = buffer;
	}
}


void insertion_sort4(int* a, int length) {
	for (int i = 1; i < length; ++i) {
		for (int k = i; k >= 1; --k) {
			if (a[k - 1] > a[k])
				Insertion_sort4::swap(a[k - 1], a[k]);
			else break;
		}
	}
}
