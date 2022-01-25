#include "heap_sort5.h"

static int left_child_index(int index) {
	return 2 * index + 1;
}
static int right_child_index(int index) {
	return left_child_index(index) + 1;
}
static bool left_child_exists(int index, int length) {
	return left_child_index(index) < length;
}
static bool right_child_exists(int index, int length) {
	return right_child_index(index) < length;
}
static void swap(int& a, int& b) {
	const int temporary = a;
	a = b;
	b = temporary;
}

void sift_down(int index, int* a, int length) {
	while (left_child_exists(index, length)) {
		const int old_index = index;

		if (right_child_exists(index, length) &&
			a[right_child_index(index)] > a[left_child_index(index)]) {
			if (a[right_child_index(index)] > a[index])
				index = right_child_index(index);
		}
		else if (a[left_child_index(index)] > a[index])
			index = left_child_index(index);

		if (index == old_index) return;

		swap(a[old_index], a[index]);
	}
}

static void heapify(int* a, int length) {
	for (int index = length / 2 + 1; index >= 0; --index)
		sift_down(index, a, length);
}

void heap_sort5(int* a, int length) {
	heapify(a, length);

	for (int index = 0; index < length - 1; ++index) {
		swap(a[0], a[length - 1 - index]);
		sift_down(0, a, length - 1 - index);
	}
}