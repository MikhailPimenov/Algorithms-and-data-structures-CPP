#include "longest_common_subsequence4.h"

namespace Longest_common_subsequence4 {
    void reveal_subsequence(
        const int* a, int lengthA, 
        const int* b, int lengthB, 
        int **ff,
        int length, int* p_out
    ) {
        int i = lengthA;
        int j = lengthB;
        int k = length - 1;

        while (i && j) {
            if (ff[i - 1][j] == ff[i][j - 1]) {
                if (ff[i - 1][j] < ff[i][j]) {
                    p_out[k] = a[i - 1];
                    --k;
                }
                --i;
                --j;
            }
            else if (ff[i - 1][j] < ff[i][j - 1]) --j;
            else --i;
        }
    }
    int maximum(int a, int b) {
        return a > b ? a : b;
    }
    int get_length(
        const int* a, int lengthA, 
        const int* b, int lengthB, 
        int** ff
    ) {
        for (int i = 0; i < lengthA + 1; ++i)
            ff[i][0] = 0;
        for (int j = 0; j < lengthB + 1; ++j)
            ff[0][j] = 0;

        for (int i = 1; i < lengthA + 1; ++i)
            for (int j = 1; j < lengthB + 1; ++j)
                if (a[i - 1] == b[j - 1])
                    ff[i][j] = ff[i - 1][j - 1] + 1;
                else
                    ff[i][j] = maximum(ff[i - 1][j], ff[i][j - 1]);

        return ff[lengthA][lengthB];
    }
}

int longest_common_subsequence4(const int* a, int lengthA, const int* b, int lengthB, int*& p_out)
{
    int* f = new int[(lengthA + 1) * (lengthB + 1)];
    int** ff = new int* [lengthA + 1];

    for (int i = 0; i < lengthA + 1; ++i)
        ff[i] = f + i * (lengthB + 1);

    int length = Longest_common_subsequence4::get_length(a, lengthA, b, lengthB, ff);
    p_out = new int[length];
    Longest_common_subsequence4::reveal_subsequence(
        a, lengthA, 
        b, lengthB, 
        ff, length, p_out
    );

    delete[] ff;
    delete[] f;

    return length;
}
