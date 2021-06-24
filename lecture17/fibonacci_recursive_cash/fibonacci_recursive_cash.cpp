#include "fibonacci_recursive_cash.h"

long long _fib ( int n, long long *cash )
{
    if ( n < 2 )
    {
        if ( cash[n] == -1 )
            cash[n] = 1;
        return cash[n];
    }

    if ( cash[n] == -1 )
        cash[n] = _fib ( n - 1, cash ) + _fib ( n - 2, cash );

    return cash[n];
}
long long fibonacci_recursive_cash ( int n )
{
    if ( n <= 0 || n > 10000 )
        return -1;

    long long *cash = new long long[static_cast < unsigned > ( n + 1 )];
    for ( int index = 0; index < n + 1; ++index )
        cash[index] = -1;

    long long result = _fib ( n, cash );



    delete [] cash;

    return result;
}
