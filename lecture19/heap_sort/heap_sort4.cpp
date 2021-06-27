#include "heap_sort4.h"

namespace Heap_sort4 {
	int child1_index(int i) {
		return 2 * i + 1;
	}
	int child2_index(int i) {
		return child1_index(i) + 1;
	}
	int child1_exists(int length, int i) {
		return child1_index(i) < length;
	}
	int child2_exists(int length, int i) {
		return child2_index(i) < length;
	}

	void swap(int& x, int& y) {
		int buffer = x;
		x = y;
		y = buffer;
	}

	void sift_down(int* a, int length, int i) {
		while (child1_exists(length, i)) {
			int old = i;

			if (child2_exists(length, i) && a[child2_index(i)] > a[child1_index(i)]) {
				if (a[child2_index(i)] > a[i]) i = child2_index(i);
			}
			else if (a[child1_index(i)] > a[i]) i = child1_index(i);

			if (i != old) swap(a[old], a[i]);
			else return;
		}
	}
	void heapify(int* a, int length) {
		for (int i = length / 2; i >= 0; --i)
			sift_down(a, length, i);
	}
}

void heap_sort4(int* a, int length)
{
	Heap_sort4::heapify(a, length);

	for (int i = 0; i < length - 1; ++i) {
		Heap_sort4::swap(a[0], a[length - 1 - i]);
		Heap_sort4::sift_down(a, length - 1 - i, 0);
	}
}
