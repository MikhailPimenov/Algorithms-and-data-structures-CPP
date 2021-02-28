#include "hoar_sort2.h"
namespace Hoar_sort2 {
    void swap_elements ( int *array, int index1, int index2 )
    {
        int buffer =  array[index1];
        array[index1] = array[index2];
        array[index2] = buffer;
    }
}
void hoar_sort2 ( int *array, int length )
{
    if ( length < 2 ) return;

    int pivot_index = 0; // must be random
    int pivot = array[pivot_index];

    int lower = 0;
    int greater = 0;

    for ( int index = 0; index < length; ++index ) {
        if ( array[index] < pivot ) ++lower;
        else if ( array[index] > pivot ) ++greater;
    }
    int equal = length - lower - greater;

    int lower_index = 0;
    int equal_index = lower;
    int greater_index = length - 1;

    while ( equal_index <= greater_index ) {
        if ( array[greater_index] > pivot ) {
            --greater_index;
        } else if ( array[greater_index] < pivot ) {
            Hoar_sort2::swap_elements ( array, greater_index, lower_index );
            ++lower_index;
        } else {
            Hoar_sort2::swap_elements ( array, greater_index, equal_index );
            ++equal_index;
        }
    }

    hoar_sort2 ( array, lower );
    hoar_sort2 ( array + lower + equal, greater );
}
