#include "merge_sort.h"

void _merge ( int *array, int length, const int *array1, int length1, const int *array2, int length2 )
{
    assert ( length == length1 + length2 );

    int index = 0;
    int index1 = 0;
    int index2 = 0;

    while ( index1 < length1 && index2 < length2 )
    {
        if ( array1[index1] <= array2[index2] )
        {
            array[index] = array1[index1];
            ++index1;
        }
        else
        {
            array[index] = array2[index2];
            ++index2;
        }
        ++index;
    }

    while ( index1 < length1 )
    {
        array[index] = array1[index1];
        ++index1;
        ++index;
    }
    while ( index2 < length2 )
    {
        array[index] = array2[index2];
        ++index2;
        ++index;
    }
}
void _copy ( const int *source, int *destination, int length )
{
    for ( int index = 0; index < length; ++index )
        destination[index] = source[index];
}
void _merge_sort_recursive ( int *array, int *buffer_array, int length )
{
    if ( length < 2 )
        return;

    _merge_sort_recursive ( array,
                            buffer_array,
                            length / 2 );

    _merge_sort_recursive ( array + length / 2,
                            buffer_array + length / 2,
                            length - length / 2 );

    _merge ( array, length,
             buffer_array, length / 2,
             buffer_array + length / 2, length - length / 2 );

    _copy ( array, buffer_array, length );
}
void merge_sort ( int *array, int length )
{
    int *buffer_array = new int[static_cast < unsigned > ( length )];
    _copy ( array, buffer_array, length );

    _merge_sort_recursive ( array, buffer_array, length );

    delete [] buffer_array;
}
