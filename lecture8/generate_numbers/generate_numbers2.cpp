#include "generate_numbers2.h"

namespace Generate_numbers2 {
	void print_array(const int* array, int length)
	{
		for (int index = 0; index < length; ++index)
			std::cout << array[index];
		std::cout << std::endl;
	}
}

void generate_numbers_recursive2(int base, int length, int initial_length, int* array)
{
	if (length < 1) {
		Generate_numbers2::print_array(array, initial_length);
		return;
	}

	for (int digit = 0; digit < base; ++digit) {
		array[initial_length - length] = digit;
		generate_numbers_recursive2(base, length - 1, initial_length, array);
	}
}

void generate_numbers2(int base, int length)
{
	int* array = new int[length];
	for (int current_length = 1; current_length <= length; ++current_length) {
		generate_numbers_recursive2(base, current_length, current_length, array);
	}
	delete[] array;
}

