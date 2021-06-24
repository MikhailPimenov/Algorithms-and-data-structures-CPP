#include "chess_queen.h"

int chess_queen ( int m, int n )
{
    assert ( m > 0 && n > 0 );
    int *deck_array = new int[static_cast < unsigned > ( ( m + 1 ) * ( n + 1 ) )];

    int **deck = new int*[static_cast < unsigned > ( m + 1 )];
    for ( int i = 0; i < m + 1; ++i )
        deck[i] = deck_array + i * ( n + 1 );

    for ( int i = 0; i < m + 1; ++i )
        deck[i][0] = 0;
    for ( int j = 0; j < n + 1; ++j )
        deck[0][j] = 0;

    deck[1][1] = 1;

    for ( int i = 1; i < m + 1; ++i )
    {
        for ( int j = 1; j < n + 1; ++j )
        {
            if ( ( i != 1 ) || ( j != 1 ) )
            deck[i][j] = deck[i - 1][j] + deck[i][j - 1];
        }
    }

    int result = deck[m][n];

    delete [] deck;
    delete [] deck_array;

    return result;
}
