#include "grand_common_divisor4.h"

int grand_common_divisor4(int a, int b) {
    return a ? grand_common_divisor4(b % a, a) : b;
}