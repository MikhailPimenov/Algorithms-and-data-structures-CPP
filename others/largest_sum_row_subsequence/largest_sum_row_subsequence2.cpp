#include "largest_sum_row_subsequence2.h"

static void update_maximum(int current_sum, int& max_sum) {
	if (current_sum > max_sum)
		max_sum = current_sum;
}
static void move_right(const int* a, int length, int& right, int& current_sum) {
	assert(right + 1 < length && "Right index is out of range!");

	++right;
	current_sum += a[right];
}
static void move_left(const int* a, int length, int& left, int& current_sum) {
	assert(left + 1 < length && "Left index is out of range!");

	current_sum -= a[left];
	++left;
}
static void move_both(const int* a, int length, int& left, int& right, int& current_sum) {
	move_right(a, length, right, current_sum);
	move_left(a, length, left, current_sum);
}


int largest_sum_row_subsequence2(const int* a, int length) {
	int max_sum{ 0 };
	int current_sum{ a[0] };
	int left{ 0 };
	int right{ 0 };

	do{
		if (current_sum >= 0 && right + 1 < length) {
			move_right(a, length, right, current_sum);
		}
		else if (right == left) {
			move_both(a, length, left, right, current_sum);
		}
		else { // (current_sum < 0 or right + 1 == length) and right != left
			move_left(a, length, left, current_sum);
		}

		update_maximum(current_sum, max_sum);

	} while (right + 1 < length && left + 1 < length);

	return max_sum;
}
