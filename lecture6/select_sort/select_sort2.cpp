#include "select_sort2.h"

void select_sort2 ( int *array, int length )
{
    for ( int element_index = 0; element_index < length - 1; ++element_index ) {
        int max_index = 0;

        for ( int search_index = 1; search_index < length - element_index; ++search_index ) {
            if ( array[search_index] > array[max_index] )
                max_index = search_index;
        }
        int buf = array[max_index];
        array[max_index] = array[length - 1 - element_index];
        array[length - 1 - element_index] = buf;
    }
}
