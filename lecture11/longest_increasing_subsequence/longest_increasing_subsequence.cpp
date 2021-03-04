#include "longest_increasing_subsequence.h"
int calculate_length ( const int *sequence, int length, int *f )
{
    for ( int currentIndex = 1; currentIndex < length + 1; ++currentIndex )
    {
        int max = 0;
        int maxIndex = 0;
        for ( int searchIndex = 1; searchIndex < currentIndex; ++searchIndex )
        {
            if ( ( f[searchIndex] > max ) && ( sequence[currentIndex - 1] > sequence[searchIndex - 1] ) )
            {
                max = f[searchIndex];
                maxIndex = searchIndex;
            }
        }
        f[currentIndex] = max + 1;
    }

    int result = 0;
    for ( int index = 1; index < length + 1; ++index )
    {
        if ( f[index] > result )
            result = f[index];
    }

    return result;
}
int* allocate_and_init ( int length )
{
    int *f = new int[static_cast < unsigned > ( length + 1)];
    f[0] = 0;

    return f;
}
void delete_allocated ( int *&f )
{
    delete [] f;
}
void subsequence ( const int *sequence, int length, const int *f, int *subsequenceOut, int sub_length )
{
    assert ( subsequenceOut );
    int currentMaxIndex = Common::max ( f, length + 1 );

    int sub_index = sub_length - 1;
    subsequenceOut[sub_index] = sequence[currentMaxIndex - 1];
    --sub_index;

    for ( int index = currentMaxIndex; index >= 1; --index )
    {
        if ( f[index] == f[currentMaxIndex] - 1 )
        {
            subsequenceOut[sub_index] = sequence[index - 1];
            --sub_index;
            currentMaxIndex = index;
        }
    }
}
int longest_increasing_subsequence ( const int *sequence, int length, int *subsequenceOut )
{
    int *f = allocate_and_init ( length );

    int result = calculate_length ( sequence, length, f );

    subsequence ( sequence, length, f, subsequenceOut, result );

    delete_allocated ( f );

    return result;
}
