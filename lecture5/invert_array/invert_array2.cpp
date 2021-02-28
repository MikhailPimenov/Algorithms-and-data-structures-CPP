#include "invert_array2.h"

void invert_array2 ( int *array, int length )
{
    for ( int index = 0; index < length / 2; ++index ) {
        int buffer = array[index];
        array[index] = array[length - index - 1];
        array[length - index - 1] = buffer;
    }
}
