#include "largest_sum_row_subsequence.h"

int sum ( const int *array, int length, int first_index, int last_index )
{
    assert ( first_index >= 0 );
    assert ( first_index <= last_index );
    assert ( last_index >= 0 );
    assert ( last_index <= length );

    int result = 0;
    for ( int index = first_index; index < last_index; ++index )
        result += array[index];

    return result;
}

int find_max ( const int *array, int length )
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
void allocate_and_init1 ( int length, int *&fOut, int **&ffOut )
{
    fOut = new int[static_cast < unsigned > ( ( length + 1 ) * ( length + 1 ) )];

    ffOut = new int*[static_cast < unsigned > ( length + 1 )];
    for ( int i = 0; i < length + 1; ++i )
        ffOut[i] = fOut + ( length + 1 ) * i;

    for ( int i = 0; i < length + 1; ++i )
        for ( int j = 0; j < length + 1; ++j )
            ffOut[i][j] = 0;

}
void delete_all1 ( int *&fOut, int **&ffOut )
{
    delete [] ffOut;
    delete [] fOut;
}
int largest_sum_row_subsequence ( const int *array, int length )
{
    int *f = nullptr;
    int **ff = nullptr;
    allocate_and_init1 ( length, f, ff );


    for ( int i = 1; i < length + 1; ++i )
    {
        for ( int j = 1; j < i + 1; ++j )
        {
            if ( j == i )
            {
                int *sums = new int[static_cast < unsigned > ( j ) ];

                for ( int s = 0; s < j; ++s )
                {
                    sums[s] = ff[i][j - ( s + 1 )];
                    sums[s] += sum ( array, length, j - ( s + 1 ) , j - 1  );
                }
                int max = sums[find_max ( sums, j )];
                delete [] sums;

                if ( max > 0 )
                    ff[i][j] = array[i - 1] + max;
                else
                    ff[i][j] = array[i - 1];
            }
            else
                ff[i][j] = ff[i - 1][j];
        }
    }
    int result = ff[length][find_max( ff[length], length + 1 )];

    delete_all1 ( f, ff );

    return result;
}
