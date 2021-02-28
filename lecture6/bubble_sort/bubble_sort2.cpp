#include "bubble_sort2.h"

void bubble_sort2 ( int *array, int length )
{
    for ( int index1 = 0; index1 < length - 1; ++index1 ) {
        bool go_on = false;
        for ( int index2 = 0; index2 < length - index1 - 1; ++index2 ) {
            if ( array[index2] > array[index2 + 1] ) {
                int buf = array[index2];
                array[index2] = array[index2 + 1];
                array[index2 + 1] = buf;
                go_on = true;
            }
        }
        if ( !go_on ) break;
    }
}
