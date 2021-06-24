#include "knuth_morris_pratt.h"

void allocate_and_init ( const char *cString, const char *cSubstring,
                         int length, int sub_length,
                         char *&superstringOut, int *&p_arrayOut )
{
    superstringOut = new char[static_cast < unsigned > ( sub_length + 1 + length + 1 )];

    for ( int index = 0; index < sub_length; ++index )
        superstringOut[index] = cSubstring[index];

    superstringOut[sub_length] = '#';

    for ( int index = 0; index < length; ++index )
        superstringOut[index + sub_length + 1] = cString[index];

    superstringOut[sub_length + 1 + length] = '\0';

    p_arrayOut = new int[static_cast < unsigned > ( sub_length + 1 + length )];
}
void delete_all ( char *&superstring, int *&p_array )
{
    delete [] superstring;
    delete [] p_array;

    superstring = nullptr;
    p_array = nullptr;
}
int kmp ( const int *p_array, int length, int sub_length )
{
    int result = -1;
    for ( int index = 0; index < sub_length + 1 + length; ++index )
    {
        if ( p_array[index] == sub_length )
        {
            result = index - sub_length - sub_length;
            break;
        }
    }
    return result;
}
int knuth_morris_pratt ( const char *cString, const char *cSubstring )
{
    int length = Common::length ( cString ) - 1;
    int sub_length = Common::length ( cSubstring ) - 1;

    if ( length == 0 || sub_length == 0 )
        return -1;

    char *superstring = nullptr;
    int *p_array = nullptr;

    allocate_and_init ( cString, cSubstring, length, sub_length, superstring, p_array );

    p_function ( superstring, p_array, sub_length + 1 + length );

    int result = kmp ( p_array, length, sub_length );

    delete_all ( superstring, p_array );

    return result;
}
