#include "eratoshenes_sieve.h"

void eratosthenes_sieve ( int n )
{
    bool *array = new bool [ static_cast < unsigned > ( n ) ];
    for ( int index = 0; index < n; ++index )
        array[index] = true;

    for ( int divisor = 2; divisor < n / 2; ++divisor )
    {
        for ( int index = divisor * 2; index < n; index += divisor )
            array[index] = false;
    }

    for ( int index = 0; index < n; ++index )
        if ( array[index] )
            std::cout << index << '\n';

    delete [] array;
}

