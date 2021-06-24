#include "invert_array.h"

void invert_array ( int *array, int length )
{
    for ( int index = 0; index < length / 2; ++index )
    {
        int temp                  = array[index];
        array[index]              = array[length - 1 - index];
        array[length - 1 - index] = temp;
    }
}

