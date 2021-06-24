#include "insert_sort.h"

void insert_sort ( int *array, int length )
{
    for ( int current_index = 1; current_index < length; ++current_index )
    {
        int index = current_index;
        for ( int inner_index = current_index - 1; inner_index >= 0; --inner_index )
        {
            if ( array[index] < array[inner_index] )
            {
                Common::swap ( array[index], array[inner_index] );
                --index;
            }
            else
                break;
        }
    }
}
