#include "generate_permutations2.h"

namespace Generate_permutations2 {
	void print_array(const int* array, int length)
	{
		for (int index = 0; index < length; ++index)
			std::cout << array[index] << ' ';
		std::cout << '\n';
	}
	bool find(int element, const int* array, int length)
	{
		for (int index = 0; index < length; ++index)
		{
			if (array[index] == element)
				return true;
		}
		return false;
	}
}

void generate_permutations_recursive2(const int* items, int items_length,
	int* permutation, int permutation_length,
	int initial_permutation_length)
{
	if (permutation_length < 1) {
		Generate_permutations2::print_array(permutation, initial_permutation_length);
		return;
	}

	for (int item_index = 0; item_index < items_length; ++item_index)
	{
		if (!(Generate_permutations2::find(items[item_index], permutation,
			initial_permutation_length - permutation_length))) {
			permutation[initial_permutation_length - permutation_length] = items[item_index];

			generate_permutations_recursive2(items, items_length,
				permutation, permutation_length - 1, initial_permutation_length);
		}

		//generate_permutations_recursive2(items, items_length,
			//permutation, permutation_length - 1, initial_permutation_length - 1);

	}
}



void generate_permutations2(const int* items, int items_length,
	int permutation_length)
{
	int* permutation = new int[permutation_length];

	for (int length = 1; length <= permutation_length; ++length)
		generate_permutations_recursive2(items, items_length, permutation, length, length);

	delete[] permutation;
}
