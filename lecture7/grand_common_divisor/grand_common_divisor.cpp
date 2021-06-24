#include "grand_common_divisor.h"

int grand_common_divisor ( int a, int b )
{
    if ( !a || !b )
        return 1;

    if ( a % b == 0 )
        return b;

    return grand_common_divisor ( b, a % b );
}
