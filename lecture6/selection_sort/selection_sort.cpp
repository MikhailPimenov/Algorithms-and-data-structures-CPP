#include "selection_sort.h"

void selection_sort ( int *array, int length )
{
    for ( int current_index = 0; current_index < length - 1; ++current_index )
    {
        int minimum_index   = current_index;
        int minimum_element = array[minimum_index];

        for ( int search_index = current_index + 1; search_index < length; ++search_index )
        {

            if ( array[search_index] < minimum_element )
            {
                minimum_element = array[search_index];
                minimum_index   = search_index;
            }
        }
        Common::swap ( array[current_index], array[minimum_index] );
    }
}
