#include "longest_increasing_subsequence4.h"

namespace Longest_increasing_subsequence4 {
    int get_length(const int* a, int lengthA, int *f) {
        for (int i = 0; i < lengthA; ++i) {
            int maximum = 0;
            for (int j = 0; j < i; ++j) {
                if (f[j] > maximum && a[i] > a[j]) {
                    maximum = f[j];
                }
            }
            f[i] = 1 + maximum;
        }
        
        int result = 0;
        for (int i = 0; i < lengthA; ++i)
            if (f[i] > result)
                result = f[i];

        return result;
    }

    void reveal_subsequence(const int* a, int lengthA, const int* f, int length, int* p_out) {
        int i = 0;
        for (int j = 0; j < lengthA; ++j) {
            if (f[j] == length) {
                i = j;
                break;
            }
        }

        p_out[length - 1] = a[i];
        --i;
        int k = length - 2;
        int maximum = length;

        while (maximum > 1) {
            if (f[i] == maximum - 1) {
                p_out[k] = a[i];
                --k;
                --maximum;
            }
            --i;
        }   
    }
}

int longest_increasing_subsequence4(const int* a, int lengthA, int*& p_out) {
    int* f = new int[lengthA];

    int length = Longest_increasing_subsequence4::get_length(a, lengthA, f);
    p_out = new int[length];

    Longest_increasing_subsequence4::reveal_subsequence(a, lengthA, f, length, p_out);

    delete[] f;
    return length;
}
