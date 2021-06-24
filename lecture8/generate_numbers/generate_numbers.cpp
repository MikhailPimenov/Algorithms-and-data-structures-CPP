#include "generate_numbers.h"

void print ( const int *array, int length )
{
    for ( int index = 0; index < length; ++index )
    {
        if ( array + index )
            std::cout << array[index];
        else
            return;
    }
    std::cout << '\n';
}
void _generate_numbers ( int *array, int initial_length, int base, int length )
{
    if ( length < 1 )
    {
        print ( array, initial_length );
        return;
    }

    for ( int digit = 0; digit < base; ++digit )
    {
        array[initial_length - length] = digit;
        _generate_numbers ( array, initial_length, base, length - 1 );
    }
}
void generate_numbers ( int base, int length )
{
    if ( base > 10 )
        return;

    int *array = new int[static_cast < unsigned > ( length )];

    _generate_numbers ( array, length, base, length );

    delete [] array;
}
