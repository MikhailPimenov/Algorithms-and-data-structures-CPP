#include "common.h"

namespace Common {

int max ( int a, int b )
{
    return ( a > b ) ? a : b;
}
int min ( int a, int b )
{
    return ( a <= b ) ? a : b;
}
int max ( const int *array, int length )
{
    if ( ! array )
        return -1;

    int maximum = array[0];
    int maximumIndex = 0;

    for ( int index = 0; index < length; ++index )
    {
        if ( array + index )
        {
            if ( array[index] > maximum )
            {
                maximum = array[index];
                maximumIndex = index;
            }
        }
        else
        {
            return -1;
        }
    }
    return maximumIndex;
}
bool is_equal ( const int *array1, const int *array2, int length )
{
    for ( int index = 0; index < length; ++index )
    {
        if ( array1 + index && array2 + index )
        {
            if ( array1[index] != array2[index] )
                return false;
        }
        else if ( ( array1 + index ) || ( array2 + index ) )
            return false;
    }

    return true;
}
int length ( const char *cString )
{
    if ( ! cString )
        return 0;

    int result = 0;
    while ( cString + result && cString[result] != '\0' )
        ++result;

    ++result;
    return result;
}
void print ( const int *array, int length )
{
    for ( int index = 0; index < length; ++index )
        if ( array + index )
            std::cout << array[index] << ' ';
    std::cout << '\n';
}
bool is_sorted ( const int *array, int length, bool ascending )
{
    int sign = 2 * static_cast < int > ( ascending ) - 1;
    for ( int index = 0; index < length - 1; ++index )
    {
        if ( array + index && array + index + 1 )
        {
            if ( array[index] * sign > array[index + 1] * sign )
                return false;
        }
        else
            break;
    }
    return true;
}
void swap ( int &a, int &b )
{
    int t = a;
    a = b;
    b = t;
}

}
