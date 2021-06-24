#include "binary_search.h"

//int array[] { 1, 1, 1, 1, 1, 2, 2, 3, 4, 4, 4, 6, 6, 7, 7, 7, 7, 7, 8, 9 };
int left_boundary ( int *array, int length, int element )
{
    int left   = -1;
    int right  = length;
    int middle = 0;

    while ( right - left > 1 )
    {
        middle = left + ( right - left ) / 2;
        if ( array[middle] >= element )
            right = middle;
        else
            left = middle;
    }
    return left;
}
int right_boundary ( int *array, int length, int element )
{
    int left   = -1;
    int right  = length;
    int middle = 0;

    while ( right - left > 1 )
    {
        middle = left + ( right - left ) / 2;
        if ( array[middle] > element )
            right = middle;
        else
            left = middle;
    }
    return right;
}
bool binary_search ( int *array, int length, int element, int &leftOut, int &rightOut )
{
    leftOut = left_boundary ( array, length, element );
    rightOut = right_boundary ( array, length, element );

    return ( rightOut - leftOut ) > 1;
}
