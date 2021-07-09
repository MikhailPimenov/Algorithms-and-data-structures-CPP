#include "generate_permutations4.h"

namespace Generate_permutations4{
	void print_array(const int* array, int length) {
		for (int index = 0; index < length; ++index)
			std::cout << array[index] << ' ';
		std::cout << '\n';
	}
	void generate_permutations_recursive(const int* items, int length, int* prefix, int permutation_length, int n) {
		if (!n) {
			print_array(prefix, permutation_length);
			return;
		}

		for (int i = 0; i < length; ++i) {
			prefix[permutation_length - n] = items[i];
			generate_permutations_recursive(items, length, prefix, permutation_length, n - 1);
		}
	}
}

void generate_permutations4(const int* items, int length, int n) {
	int* prefix = new int[length];

	Generate_permutations4::generate_permutations_recursive(items, length, prefix, n, n);

	delete[] prefix;
}
