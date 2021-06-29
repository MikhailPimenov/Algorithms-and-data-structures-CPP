#include "levenstein4.h"

namespace Levenstein4 {
    int get_length(const char* s) {
        int length = 0;
        while (s[length] != '\0')
            ++length;

        ++length;
        return length;
    }

    int minimum(int a, int b, int c) {
        int m = a <= b ? a : b;
        return m <= c ? m : c;
    }
}

int levenstein4(const char* a, int lengthA, const char* b, int lengthB) {
    int* f = new int[(lengthA + 1) * (lengthB + 1)];
    int** ff = new int* [lengthA + 1];

    for (int i = 0; i < lengthA + 1; ++i) {
        ff[i] = f + i * (lengthB + 1);
    }

    for (int i = 0; i < lengthA + 1; ++i) {
        ff[i][0] = i;
    }
    for (int j = 0; j < lengthB + 1; ++j) {
        ff[0][j] = j;
    }

    for (int i = 1; i < lengthA + 1; ++i) {
        for (int j = 1; j < lengthB + 1; ++j) {
            if (a[i - 1] == b[j - 1])
                ff[i][j] = ff[i - 1][j - 1];
            else
                ff[i][j] = 1 + Levenstein4::minimum(ff[i - 1][j], ff[i][j - 1], ff[i - 1][j - 1]);
        }
    }

    int result = ff[lengthA][lengthB];

    delete[] ff;
    delete[] f;

    return result;
}

int levenstein4_adapted(const char* a, const char* b) {
    int lengthA = Levenstein4::get_length(a) - 1;
    int lengthB = Levenstein4::get_length(b) - 1;

    return levenstein4(a, lengthA, b, lengthB);
}
