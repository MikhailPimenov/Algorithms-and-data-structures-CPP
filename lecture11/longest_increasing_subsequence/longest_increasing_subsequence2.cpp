#include "longest_increasing_subsequence2.h"


int* allocate_target_array(int length)
{
	int* f = new int[length];
	return f;
}
int* allocate_result_array(int result_length)
{
	return allocate_target_array(result_length);
}
int get_length_of_longest_increasing_subsequence(const int* array, int length, int* f)
{
	for (int i = 0; i < length; ++i)
	{
		int max = 0;
		for (int j = 0; j < i; ++j) {
			if (array[i] > array[j] && f[j] > max)
				max = f[j];
		}
		f[i] = 1 + max;
	}

	int result_length = 0;

	for (int i = 0; i < length; ++i)
		if (f[i] > result_length)
			result_length = f[i];

	return result_length;
}

void free_target_array(int*& f) {
	delete[] f;
}

void reveal_subsequence(const int* array, int length, int* array_out, int result_length, int* f)
{
	int max_index = 0;
	for (int i = 0; i < length; ++i) {
		if (f[i] > f[max_index])
			max_index = i;
	}

	int r = result_length - 1;
	array_out[r] = array[max_index];
	--r;

	int i = max_index;

	while (i >= 0) {
		if (f[i] == f[max_index] - 1) {
			max_index = i;
			array_out[r] = array[max_index];
			--r;
		}
		--i;
	}
}

int longest_increasing_subsequence2(const int* array, int length, int*& array_out)
{
	int* f = allocate_target_array(length);

	int result_length = get_length_of_longest_increasing_subsequence(array, length, f);

	array_out = allocate_result_array(result_length);

	reveal_subsequence(array, length, array_out, result_length, f);

	free_target_array(f);

	return result_length;
}
