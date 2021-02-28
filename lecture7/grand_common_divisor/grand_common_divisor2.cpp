#include "grand_common_divisor2.h"

int grand_common_divisor2 ( int a, int b )
{
    if ( !a && b )
        return b;
    if ( a && !b )
        return a;
    if ( !a && !b )
        return 1;

    if ( a % b == 0 )
        return b;
    return grand_common_divisor2 ( b, a % b );
}
