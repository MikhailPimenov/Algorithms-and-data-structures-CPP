#include "merge_sort2.h"

namespace Merge_sort2 {
    void copy ( int *destination, int *source, int length )
    {
        for ( int index = 0; index < length; ++index )
            destination[index] = source[index];
    }
}

void merge ( int *array, int length, int *array1, int length1, int *array2, int length2 )
{
    assert ( length == length1 + length2 );

    int index1 = 0;
    int index2 = 0;
    int index = 0;

    while ( index1 < length1 && index2 < length2 ) {
        if ( array1[index1] <= array2[index2] ) {
            array[index] = array1[index1];
            ++index1;
        } else {
            array[index] = array2[index2];
            ++index2;
        }
        ++index;
    }

    while ( index1 < length1 ) {
        array[index] = array1[index1];
        ++index;
        ++index1;

    }
    while ( index2 < length2 ) {
        array[index] = array2[index2];
        ++index;
        ++index2;
    }

}


void merge_sort_recursive ( int *array, int *buf_array, int length )
{
    if ( length < 2 ) return;

    merge_sort_recursive ( array, buf_array, length / 2 );
    merge_sort_recursive ( array + length / 2, buf_array + length / 2, length - length / 2 );

    merge ( array, length, buf_array, length / 2, buf_array + length / 2, length - length / 2 );
    Merge_sort2::copy ( buf_array, array, length );
}

void merge_sort2 ( int *array, int length )
{
    int *buf_array = new int[static_cast<unsigned> ( length )];
    Merge_sort2::copy ( buf_array, array, length );

    merge_sort_recursive ( array, buf_array, length );

    delete [] buf_array;
}
