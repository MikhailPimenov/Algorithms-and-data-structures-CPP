#include "fibonacci4.h"

int fibonacci4(int n) {
    if (n == 0 || n == 1)
        return n;
    return fibonacci4(n - 1) + fibonacci4(n - 2);
}
