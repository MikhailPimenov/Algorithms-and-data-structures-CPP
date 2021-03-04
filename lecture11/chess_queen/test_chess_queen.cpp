#include "test_chess_queen.h"

void test_chess_queen ( int ( *algorithm ) ( int, int ) )
{
    std::cout << "test_chess_queen:\n";

    int n = 8;
    int m = 8;

    for ( int i = 1; i < m + 1; ++i )
    {
        for ( int j = 1; j < n + 1; ++j )
        {
            std::cout << algorithm ( i, j ) << '\t';
        }
        std::cout << "\n\n";
    }
}

