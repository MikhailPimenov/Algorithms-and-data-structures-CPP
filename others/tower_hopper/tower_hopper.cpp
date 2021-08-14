#include "tower_hopper.h"

bool tower_hopper(const int* a, int length) {
	int left = 0;
	int right = 0;

	while (left <= right && right < length) {
		if (a[left] + left > right)
			right = a[left] + left;
		++left;
	}

	return right >= length;
}