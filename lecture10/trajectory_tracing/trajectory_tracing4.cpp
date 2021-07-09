#include "trajectory_tracing4.h"

int trajectory_tracing4(int* prices, bool* allowed, int length, int destination) {
    assert(destination <= length && "Destination index is out of range of prices and allowed");

    int* f = new int[length];
    for (int i = 0; i < length; ++i)
        f[i] = 0;

    if (allowed[0])
        f[0] = prices[0];
    if (allowed[1])
        f[1] = f[0] + prices[1];

    for (int i = 2; i < length; ++i) {
        if (allowed[i - 1] && allowed[i - 2])
            f[i] = prices[i] + (f[i - 1] < f[i - 2] ? f[i - 1] : f[i - 2]);
        else if (allowed[i - 1])
            f[i] = prices[i] + f[i - 1];
        else if (allowed[i - 2])
            f[i] = prices[i] + f[i - 2];
    }

    int result = f[destination - 1];
    delete[] f;

    return result;
}
