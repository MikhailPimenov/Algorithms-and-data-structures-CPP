#include "eratosthenes_sieve2.h"


void eratosthenes_sieve2 ( int number )
{
    bool *array = new bool[static_cast<unsigned> ( number )];

    for ( unsigned int index = 0; index < static_cast<unsigned> ( number ); ++index )
        array[index] = true;

    for ( unsigned int divisor = 2; divisor < std::sqrt ( number ) + 1; ++divisor )
        for ( unsigned int index = 2 * divisor; index < static_cast<unsigned> ( number ); index += divisor )
            array[index] = false;

    for ( unsigned int index = 0; index < static_cast<unsigned> ( number ); ++index )
        if ( array[index] )
            std::cout << index << std::endl;

    delete [] array;
}


