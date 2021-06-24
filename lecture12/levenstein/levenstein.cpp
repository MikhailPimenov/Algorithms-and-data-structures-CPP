#include "levenstein.h"

int min3 ( int a, int b, int c )
{
    int minAB = ( a <= b ) ? a : b;
    return ( minAB <= c ) ? minAB : c;
}
void allocate_and_init ( int length1, int length2, int *&fOut, int **&ffOut, int )
{
    fOut = new int[static_cast < unsigned > ( ( length1 + 1 ) * ( length2 + 1 ) )];
    ffOut = new int*[static_cast < unsigned > ( length1 + 1 )];
    for ( int index1 = 0; index1 < length1 + 1; ++index1 )
        ffOut[index1] = fOut + ( length2 + 1 ) * index1;

    for ( int index1 = 0; index1 < length1 + 1; ++index1 )
        ffOut[index1][0] = index1;
    for ( int index2 = 0; index2 < length2 + 1; ++index2 )
        ffOut[0][index2] = index2;

}
void deallocate ( int *&f, int **&ff )
{
    delete [] ff;
    delete [] f;
}
int levenstein ( const char *cString1, const char *cString2 )
{
    int length1 = Common::length ( cString1 ) - 1;
    int length2 = Common::length ( cString2 ) - 1;

    int *f = nullptr;
    int **ff = nullptr;
    allocate_and_init ( length1, length2, f, ff, 0 );

    for ( int index1 = 1; index1 < length1 + 1; ++index1 )
    {
        for ( int index2 = 1; index2 < length2 + 1; ++index2 )
        {
            if ( cString1[index1 - 1] == cString2[index2 - 1] )
                ff[index1][index2] = ff[index1 - 1][index2 - 1];
            else
            {
                ff[index1][index2] = 1 + min3 ( ff[index1 - 1][index2 - 1],
                                                ff[index1 - 1][index2],
                                                ff[index1][index2 - 1] );
            }
        }
    }
    int result = ff[length1][length2];

    deallocate ( f, ff );

    return result;
}
