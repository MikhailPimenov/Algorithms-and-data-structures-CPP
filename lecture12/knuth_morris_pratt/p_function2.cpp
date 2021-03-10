#include "p_function2.h"

void p_function2(const char* array, int* p_out, int length)
{
	p_out[0] = 0;
	int p_index = 0;

	for (int i = 1; i < length; ++i) {
		p_index = p_out[i - 1];
		while (true) {
			if (array[i] == array[p_index]) {
				p_out[i] = p_index + 1;
				break;
			}
			else {
				if (p_index == 0) {
					p_out[i] = 0;
					break;
				}
				p_index = p_out[p_index - 1];
			}
		}
	}
}
