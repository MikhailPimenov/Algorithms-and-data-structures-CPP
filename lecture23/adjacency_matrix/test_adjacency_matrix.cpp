#include "test_adjacency_matrix.h"

bool is_equal ( const char *array1, const char *array2, int length )
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
void test_adjacency_matrix ( int ( *algorithm ) ( int *&matrixOut, char *&vertexes, int *&indexes ) )
{
    std::cout << "test_adjacency_matrix:\n";

//         4 5
//         A B
//         B C
//         C D
//         D B
//         A D
    char vertexes[] { 'A', 'B', 'C', 'D' };
    int length = sizeof ( vertexes ) / sizeof ( vertexes[0] );

    int indexes[] { 1, 2, 3, 4, };

    int matrix[]
    {
         0, 0, 0, 0, 0 ,
         0, 0, 1, 0, 1 ,
         0, 1, 0, 1, 1 ,
         0, 0, 1, 0, 1 ,
         0, 1, 1, 1, 0 ,
    };
    int matrix_length = sizeof ( matrix ) / sizeof ( matrix[0] );


    char *vertexes_result = nullptr;
    int   *indexes_result = nullptr;
    int    *matrix_result = nullptr;

    algorithm ( matrix_result, vertexes_result, indexes_result );

    bool success = is_equal ( vertexes, vertexes_result, length )
                   && Common::is_equal ( indexes, indexes_result, length )
                   && Common::is_equal ( matrix, matrix_result, matrix_length );

    std::cout << "test #1: " << ( ( success ) ? "ok" : "FAILED" ) << '\n';

    if ( vertexes_result )
        delete [] vertexes_result;
    if ( indexes_result )
        delete [] indexes_result;
    if ( matrix_result )
        delete [] matrix_result;
}
