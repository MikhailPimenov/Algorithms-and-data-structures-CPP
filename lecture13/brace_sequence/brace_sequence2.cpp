#include "brace_sequence2.h"

namespace Brace_sequence2 {
	int get_length2(const char* array) {
		int length = 0;
		while (array[length] != '\0')
			++length;
		++length; // for '\0'

		return length;
	}
}

bool brace_sequence2(const char* array, int length) {
	char b1o = '(';
	char b2o = '[';
	char b1c = ')';
	char b2c = ']';

	std::stack < char > stack;

	for (int i = 0; i < length; ++i)
	{
		if (array[i] == b1o || array[i] == b1c || array[i] == b2o || array[i] == b2c) {
			if (array[i] == b1o || array[i] == b2o) {
				stack.push(array[i]);
			}
			else {
				if (stack.empty()) return false;
				if (array[i] == b1c) {
					if (stack.top() != b1o) return false;
					else stack.pop();
				}
				else {
					if (stack.top() != b2o) return false;
					else stack.pop();
				}
			}
		}
	}
	return stack.empty();
}

bool brace_sequence_adapted2(const char* array) {
	int length = Brace_sequence2::get_length2(array);
	return brace_sequence2(array, length);
}

