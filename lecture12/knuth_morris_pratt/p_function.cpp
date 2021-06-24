#include "p_function.h"

void p_function ( const char *cString , int *p_array, int length )
{
    assert ( p_array );

    int p_index = 0;
    p_array[0] = 0;
    for ( int index = 1; index < length; ++index )
    {
        p_index = index - 1;
        do
        {
            if ( cString[index] == cString[p_array[p_index]] )
            {
                p_array[index] = p_array[p_index] + 1;
                break;
            }
            p_index = p_array[p_index];
        }
        while ( p_index > 0 );

        if ( p_index == 0 )
            p_array[index] = 0;
    }
}
