#include "bubble_sort.h"

void bubble_sort ( int *array, int length )
{
    for ( int outer = 0; outer < length; ++outer )
    {
        for ( int inner = 0; inner < length - outer - 1; ++inner )
        {
            if ( array[inner] > array[inner + 1] )
                Common::swap ( array[inner], array[inner + 1] );
        }
    }
}
