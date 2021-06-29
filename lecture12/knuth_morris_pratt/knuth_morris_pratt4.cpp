#include "knuth_morris_pratt4.h"

int knuth_morris_pratt4(const char* s, int length, const char* ss, int slength) {
    if (length == 1 && slength == 1)
        return -1;
    
    int long_length = slength - 1 + length;
    char* ls = new char[long_length];

    for (int i = 0; i < slength - 1; ++i) {
        ls[i] = ss[i];
    }
    ls[slength - 1] = '#';

    for (int i = 0; i < length - 1; ++i) {
        ls[i + slength] = s[i];
    }

    int* p = new int[long_length];
    p_function4(ls, p, long_length);

    int result = -1;
    for (int i = 2 * (slength-1); i < long_length; ++i) {
        if (p[i] == slength - 1) {
            result = i - 2 * (slength-1);
            break;
        }
    }
    
    delete[] p;
    delete[] ls;

    return result;
}
