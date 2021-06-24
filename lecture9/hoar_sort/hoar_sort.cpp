#include "hoar_sort.h"

void hoar_sort ( int *array, int length )
{
    if ( length < 2 )
        return;

    int barrier_index = 0; // got to be random
    int barrier_element = array[barrier_index];

    int lower = 0;
    int equal = 0;
    for ( int index = 0; index < length; ++index )
    {
        if ( array[index] < barrier_element )
            ++lower;
        else if ( array[index] == barrier_element )
            ++equal;
    }
    int greater =  length - lower - equal;


    int lower_index = 0;
    int equal_index = lower;
    int greater_index = length - 1;

    while ( greater_index >= equal_index )
    {
        if ( array[greater_index] > barrier_element )
            --greater_index;
        else if ( array[greater_index] == barrier_element )
        {
            Common::swap ( array[greater_index], array[equal_index] );
            ++equal_index;
        }
        else
        {
            Common::swap ( array[greater_index], array[lower_index] );
            ++lower_index;
        }
    }

    hoar_sort ( array, lower );
    hoar_sort ( array + lower + equal, greater );
}
