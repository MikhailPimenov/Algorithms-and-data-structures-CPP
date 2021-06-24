#include "fibonacci.h"

int fibonacci_recursive ( int n )
{
    if ( n < 2 )
        return n;

    return fibonacci_recursive ( n - 1 ) + fibonacci_recursive ( n - 2 );
}

int fibonacci ( int n )
{
    int *f = new int[static_cast < unsigned > ( n )];
    f[0] = 0;
    f[1] = 1;

    for ( int index = 2; index < n; ++index )
        f[index] = f[index - 1] + f[index - 2];

    int result = f[n - 1];
    delete [] f;

    return result;
}
