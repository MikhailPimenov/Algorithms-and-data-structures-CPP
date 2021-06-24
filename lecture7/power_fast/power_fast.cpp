#include "power_fast.h"

int power_fast ( int base, int power )
{
    if ( base < 0 || power < 0 )
        return -1;

    if ( base == 0 )
        return 0;


    if ( power == 0 )
        return 1;

    if ( power % 2 )
        return power_fast ( base, power - 1 ) * base;
    else
        return power_fast ( base * base, power / 2 );
}
