#include "heap_sort3.h"


namespace Heap_sort3 {
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

int child1_index(int index) {
	return 2 * index + 1;
}
int child2_index(int index) {
	return child1_index(index) + 1;
}
bool child1_exists(int length, int index) {
	return child1_index(index) < length;
}
bool child2_exists(int length, int index) {
	return child2_index(index) < length;
}
void sift_down(int* a, int length, int i) {
	while (child1_exists(length, i)) {
		int old_i = i;
		if (child2_exists(length, i) && a[child2_index(i)] > a[child1_index(i)]) {
			if (a[child2_index(i)] > a[i]) i = child2_index(i);
		}
		else if (a[child1_index(i)] > a[i]) i = child1_index(i);

		if (i == old_i) return;
		Heap_sort3::swap(a[i], a[old_i]);
	}
}
void heapify(int* a, int length) {
	for (int i = length / 2; i >= 0; --i)
		sift_down(a, length, i);
}
void heap_sort3(int* a, int length)
{
	heapify(a, length);

	for (int i = 0; i < length - 1; ++i) {
		int temp = a[length - 1 - i];
		a[length - 1 - i] = a[0];
		a[0] = temp;
		sift_down(a, length - 1 - i, 0);
	}
}
