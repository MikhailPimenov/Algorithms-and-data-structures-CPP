#include "power_fast2.h"

int power_fast2 ( int base, int n )
{
    if ( n < 0 )
        return -1;
    if ( n == 0 )
        return 1;
    if ( n == 1 )
        return base;
    if ( n % 2 )
        return power_fast2 ( base * base, ( n - 1 ) / 2 ) * base;
    return power_fast2 ( base, n - 1 ) * base;
}
