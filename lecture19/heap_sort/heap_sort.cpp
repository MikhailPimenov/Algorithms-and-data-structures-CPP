#include "heap_sort.h"
int _child1 ( int index )
{
    return 2 * index + 1;
}
int _child2 ( int index )
{
    return _child1 ( index ) + 1;
}
bool _child1_exists ( int length, int index )
{
    return _child1 ( index ) < length;
}
bool _child2_exists ( int length, int index )
{
    return _child2 ( index ) < length;
}

void _sift_down ( int *array, int length, int index )
{
    while ( _child1_exists ( length, index ) )
    {
        int old_index = index;

        if ( _child2_exists ( length, index ) && array[_child2 ( index )] > array[_child1 ( index )] )
        {
            if ( array[_child2 ( index )] > array[index] )
                index = _child2 ( index );
        }
        else if ( array[_child1 ( index )] > array[index] )
            index = _child1 ( index );

        if ( index != old_index )
            Common::swap ( array[old_index], array[index] );
        else
            return;
    }
}
void _heapify ( int *array, int length )
{
    for ( int index = length / 2 - 1; index >= 0; --index )
        _sift_down ( array, length, index );

}
int _extract_top ( int *array, int length )
{
    int result = array[0];
    array[0] = array[length - 1];
    _sift_down ( array, length - 1, 0 );
    return result;
}
void heap_sort ( int *array, int length )
{
    _heapify ( array, length );
    for ( int index = 0; index < length; ++index )
        array[length - 1 - index] = _extract_top ( array, length - index );
}
