#include "brace_sequence3.h"

bool brace_sequence3(const char* s)
{
	int length = 0;
	while (s[length] && s[length] != '\0')
		++length;
	++length;

	char b1o = '(';
	char b1c = ')';
	char b2o = '[';
	char b2c = ']';

	std::stack <char> stack;

	for (int i = 0; i < length - 1; ++i) {
		if (s[i] == b1o || s[i] == b1c || s[i] == b2o || s[i] == b2c) {
			if (s[i] == b1c || s[i] == b2c) {
				if (stack.empty()) return false;
				if (s[i] == b1c && stack.top() != b1o) return false;
				if (s[i] == b2c && stack.top() != b2o) return false;
				stack.pop();
				continue;
			}
			stack.push(s[i]);
		}
	}

	return stack.empty();
}
