#include "max_range.h"


void max_range(const int* a, int length, int& out_left, int& out_right) {
	const std::set<int> set(a, a + length);
	const std::vector<int> vector(set.cbegin(), set.cend());
	
	std::vector<int>::const_iterator left = vector.cbegin();
	auto right = left;

	out_left = *left;
	out_right = *right;

	std::size_t max_length = 1;

	while (right + 1 < vector.cend()) {
		++right;
		if (*right != *(right - 1) + 1)
			left = right;

		if (right - left + 1 > max_length) {
			max_length = right - left + 1;
			out_left = *left;
			out_right = *right;
		}
	}


}