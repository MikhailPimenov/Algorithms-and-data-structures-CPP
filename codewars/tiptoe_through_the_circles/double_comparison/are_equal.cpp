#include "are_equal.h"

bool are_equal(double a, double b, double epsilon) {
	return a > b ? a - b < epsilon : b - a < epsilon;
}