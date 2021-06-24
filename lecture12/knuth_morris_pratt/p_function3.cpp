#include "p_function3.h"

void p_function3(const char* a, int* p_array, int length)
{
	p_array[0] = 0;

	for (int i = 1; i < length; ++i) {
		int p_index = p_array[i - 1];

		while (true) {
			if (a[i] == a[p_index]) {
				p_array[i] = p_index + 1;
				break;
			}
			if (!p_index) {
				p_array[i] = 0;
				break;
			}
			p_index = p_array[p_index - 1];
		}
	}
}
