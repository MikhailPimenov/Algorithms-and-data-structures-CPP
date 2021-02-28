#include "binary_search2.h"

namespace Binary_search2 {
	int left_boundary(const int* array, int length, int item)
	{
		int left = -1;
		int right = length;
		while (right - left > 1) {
			int middle = (right - left) / 2 + left;
			if (array[middle] < item) left = middle;
			else right = middle;
		}
		return left;
	}
	int right_boundary(const int* array, int length, int item)
	{
		int left = -1;
		int right = length;
		while (right - left > 1) {
			int middle = (right - left) / 2 + left;
			if (array[middle] > item) right = middle;
			else left = middle;
		}
		return right;
	}
}

bool binary_search2(const int* array, int length, int item, int& left_out, int& right_out)
{
	left_out = Binary_search2::left_boundary(array, length, item);
	right_out = Binary_search2::right_boundary(array, length, item);
	return (right_out - left_out) > 1 ? true : false;
}
