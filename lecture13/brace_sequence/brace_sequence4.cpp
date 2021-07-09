#include "brace_sequence4.h"

namespace Brace_sequence5 {
    int get_length(const char* s) {
        int length = 0;

        while (s[length] != '\0')
            ++length;
        ++length;

        return length;
    }
}

bool brace_sequence4(const char* s) {
    int length = Brace_sequence5::get_length(s) - 1;

    char b1o = '(';
    char b2o = '[';
    char b1c = ')';
    char b2c = ']';

    std::stack<char> stack;

    for (int i = 0; i < length; ++i) {
        if (s[i] == b1o || s[i] == b2o || s[i] == b1c || s[i] == b2c) {
            if (s[i] == b1c || s[i] == b2c) {
                if (stack.empty()) return false;
                if (s[i] == b1c && stack.top() != b1o) return false;
                if (s[i] == b2c && stack.top() != b2o) return false;
                stack.pop();
            }
            else stack.push(s[i]);
        }
    }
    return stack.empty();
}
