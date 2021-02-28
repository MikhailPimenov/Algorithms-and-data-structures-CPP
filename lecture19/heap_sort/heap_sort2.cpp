#include "heap_sort2.h"


namespace Heap_sort2 {
    void swap_elements ( int *array, int index1, int index2 )
    {
        int buffer = array[index1];
        array[index1] = array[index2];
        array[index2] = buffer;
    }
}

int child1_index ( int index )
{
    return 2 * index + 1;
}
int child2_index ( int index )
{
    return 2 * index + 2;
}
bool child1_exist ( int index, int length )
{
    return child1_index ( index ) < length;
}
bool child2_exist ( int index, int length )
{
    return child2_index ( index ) < length;
}


void sift_down ( int *array, int index, int length )
{
    while ( child1_exist ( index, length ) ) {
        int old_index = index;
        if ( child2_exist ( index, length ) && ( array[child2_index ( index )] > array[child1_index ( index )] ) ) {
            if ( array[child2_index ( index )] > array[index] ) {
                index = child2_index ( index );
            }
        } else if ( array[child1_index ( index )] > array[index] ) {
            {
                index = child1_index ( index );
            }
        }
        if ( index != old_index ) {
            Heap_sort2::swap_elements ( array, index, old_index );
        } else {
            break;
        }
    }

}

void heapify ( int *array, int length )
{
    for ( int index = length / 2 - 1; index >= 0; --index )
        sift_down ( array, index, length );
}

void heap_sort2 ( int *array, int length )
{
    heapify ( array, length );

    for ( int index = 0; index < length - 1; ++index ) {
        Heap_sort2::swap_elements ( array, 0, length - 1 - index );
        sift_down ( array, 0, length - 1 - index );
    }
}

