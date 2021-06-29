#include "p_function4.h"

void p_function4(const char* s, int* f, int length) {
    f[0] = 0;

    for (int i = 1; i < length; ++i) {
        int p = f[i - 1];

        while (true) {
            if (s[i] == s[p]) {
                f[i] = p + 1;
                break;
            }
            if (!p) {
                f[i] = 0;
                break;
            }
            p = f[p - 1];
        }
    }
}
