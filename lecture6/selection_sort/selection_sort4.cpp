#include "selection_sort4.h"

namespace Selection_sort4 {
	void swap(int& a, int& b) {
		int buffer = a;
		a = b;
		b = buffer;
	}
}

void selection_sort4(int* a, int length)
{
	for (int i = length - 1; i >= 1; --i) {
		int m = 0;
		
		for (int k = 1; k < i + 1; ++k)
			if (a[k] > a[m])
				m = k;

		Selection_sort4::swap(a[m], a[i]);
	}
}
