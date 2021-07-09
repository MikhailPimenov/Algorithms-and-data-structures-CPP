#include "power_fast4.h"

int power_fast4(int base, int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return base;
    if (n < 0)
        return -1;
    if (n % 2 == 0)
        return power_fast4(base, n - 1) * base;
    return power_fast4(base * base, (n - 1) / 2) * base;
}
