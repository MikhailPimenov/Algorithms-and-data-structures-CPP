#include "insert_sort2.h"


void insert_sort2 ( int *array, int length )
{
    for ( int i1 = 1; i1 < length; ++i1 ) {
        for ( int i2 = i1 - 1; i2 >= 0; --i2 ) {
            if ( array[i2] > array[i2 + 1] ) {
                int buf = array[i2];
                array[i2] = array[i2 + 1];
                array[i2 + 1] = buf;
            } else break;
        }
    }
}

