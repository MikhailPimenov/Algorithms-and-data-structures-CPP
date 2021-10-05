#include "largest_sum_row_subsequence2.h"

static void update_maximum(int current_sum, int& max_sum) {
	if (current_sum > max_sum)
		max_sum = current_sum;
}
static void expand_window(const int* a, int length, int& right, int& current_sum) {
	assert(right < length && "Right index is out of range!");

	++right;
	current_sum += a[right];
}
static void shrink_window(const int* a, int length, int& left, int& current_sum) {
	assert(left < length && "Left index is out of range!");

	current_sum -= a[left];
	++left;
}
static void move_window(const int* a, int length, int& left, int& right, int& current_sum) {
	expand_window(a, length, right, current_sum);
	shrink_window(a, length, left, current_sum);
}


int largest_sum_row_subsequence2(const int* a, int length) {
	int max_sum{ 0 };
	int current_sum{ a[0] };
	int left{ 0 };
	int right{ 0 };

	while (right < length && left < length) {
		update_maximum(current_sum, max_sum);

		if (current_sum >= 0 && right + 1 < length) {
			expand_window(a, length, right, current_sum);
			continue;
		}
	
		if (right == left) {
			move_window(a, length, left, right, current_sum);
			continue;
		}
		
		// (current_sum < 0 or right + 1 == length) and right != left
		shrink_window(a, length, left, current_sum);
	}

	return max_sum;
}