#include "is_between.h"

bool is_between(double a, double x_1, double x_2) {
	return (x_1 < a&& a < x_2) ||
		(x_2 < a&& a < x_1) ||
		are_equal(a, x_1) ||
		are_equal(a, x_2);
}