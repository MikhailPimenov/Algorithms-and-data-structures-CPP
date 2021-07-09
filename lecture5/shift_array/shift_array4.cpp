#include "shift_array4.h"

void shift_array4(int* a, int length, int shift){
	if (shift < 0) {
		shift = length - abs(shift) % length;
	}
	if (shift > length) {
		shift = shift % length;
	}

	int* last_elements = new int[shift];

	for (int i = length - shift; i < length; ++i) {
		last_elements[i - (length - shift)] = a[i];
	}

	for (int i = length - 1; i >= shift; --i) {
		a[i] = a[i - shift];
	}

	for (int i = 0; i < shift; ++i) {
		a[i] = last_elements[i];
	}

	delete[] last_elements;
}
