#include "test_distances.h"



void test_distances ( void ( *algorithm ) ( const Lists_t &, Distances_t &, Vertex_t ) )
{
    std::cout << "test_distances:\n";

    Lists_t adjacency_lists = {
                std::make_pair ( 'A', Vertexes_t {'B', 'C', 'D', 'E', 'F'} ),
                std::make_pair ( 'B', Vertexes_t {'A', 'G', 'H'} ),
                std::make_pair ( 'C', Vertexes_t {'A','I', 'J'} ),
                std::make_pair ( 'D', Vertexes_t {'A','K'} ),
                std::make_pair ( 'E', Vertexes_t {'A','L', 'M'} ),
                std::make_pair ( 'F', Vertexes_t {'A','O', 'N'} ),
                std::make_pair ( 'G', Vertexes_t {'B','P', 'Q'} ),
                std::make_pair ( 'H', Vertexes_t {'B','R', 'S'} ),
                std::make_pair ( 'I', Vertexes_t {'C','T', 'V'} ),
                std::make_pair ( 'J', Vertexes_t {'C','U', 'W'} ),
                std::make_pair ( 'K', Vertexes_t {'D','X', 'Y'} ),
                std::make_pair ( 'L', Vertexes_t {'E','Z'} ),
                std::make_pair ( 'M', Vertexes_t {'E'} ),
                std::make_pair ( 'N', Vertexes_t {'F'} ),
                std::make_pair ( 'O', Vertexes_t {'F'} ),
                std::make_pair ( 'P', Vertexes_t {'G'} ),
                std::make_pair ( 'Q', Vertexes_t {'G'} ),
                std::make_pair ( 'R', Vertexes_t {'H'} ),
                std::make_pair ( 'S', Vertexes_t {'H'} ),
                std::make_pair ( 'T', Vertexes_t {'I'} ),
                std::make_pair ( 'V', Vertexes_t {'I'} ),
                std::make_pair ( 'U', Vertexes_t {'J'} ),
                std::make_pair ( 'W', Vertexes_t {'J'} ),
                std::make_pair ( 'X', Vertexes_t {'K'} ),
                std::make_pair ( 'Y', Vertexes_t {'K'} ),
                std::make_pair ( 'Z', Vertexes_t {'L'} ), };

    Distances_t answer = {
                std::make_pair ( 'A', 0 ),
                std::make_pair ( 'B', 1 ),
                std::make_pair ( 'C', 1 ),
                std::make_pair ( 'D', 1 ),
                std::make_pair ( 'E', 1 ),
                std::make_pair ( 'F', 1 ),
                std::make_pair ( 'G', 2 ),
                std::make_pair ( 'H', 2 ),
                std::make_pair ( 'I', 2 ),
                std::make_pair ( 'J', 2 ),
                std::make_pair ( 'K', 2 ),
                std::make_pair ( 'L', 2 ),
                std::make_pair ( 'M', 2 ),
                std::make_pair ( 'N', 2 ),
                std::make_pair ( 'O', 2 ),
                std::make_pair ( 'P', 3 ),
                std::make_pair ( 'Q', 3 ),
                std::make_pair ( 'R', 3 ),
                std::make_pair ( 'S', 3 ),
                std::make_pair ( 'T', 3 ),
                std::make_pair ( 'V', 3 ),
                std::make_pair ( 'U', 3 ),
                std::make_pair ( 'W', 3 ),
                std::make_pair ( 'X', 3 ),
                std::make_pair ( 'Y', 3 ),
                std::make_pair ( 'Z', 3 ), };
    Distances_t result;
    algorithm ( adjacency_lists, result, 'A' );
    std::cout << "test #1: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    answer.clear();
    answer = {
                std::make_pair ( 'A', 3 ),
                std::make_pair ( 'B', 2 ),
                std::make_pair ( 'C', 4 ),
                std::make_pair ( 'D', 4 ),
                std::make_pair ( 'E', 4 ),
                std::make_pair ( 'F', 4 ),
                std::make_pair ( 'G', 3 ),
                std::make_pair ( 'H', 1 ),
                std::make_pair ( 'I', 5 ),
                std::make_pair ( 'J', 5 ),
                std::make_pair ( 'K', 5 ),
                std::make_pair ( 'L', 5 ),
                std::make_pair ( 'M', 5 ),
                std::make_pair ( 'N', 5 ),
                std::make_pair ( 'O', 5 ),
                std::make_pair ( 'P', 4 ),
                std::make_pair ( 'Q', 4 ),
                std::make_pair ( 'R', 0 ),
                std::make_pair ( 'S', 2 ),
                std::make_pair ( 'T', 6 ),
                std::make_pair ( 'V', 6 ),
                std::make_pair ( 'U', 6 ),
                std::make_pair ( 'W', 6 ),
                std::make_pair ( 'X', 6 ),
                std::make_pair ( 'Y', 6 ),
                std::make_pair ( 'Z', 6 ), };
    result.clear();
    algorithm ( adjacency_lists, result, 'R' );
    std::cout << "test #2: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    answer.clear();
    answer = {
                std::make_pair ( 'A', 1 ),
                std::make_pair ( 'B', 2 ),
                std::make_pair ( 'C', 2 ),
                std::make_pair ( 'D', 2 ),
                std::make_pair ( 'E', 0 ),
                std::make_pair ( 'F', 2 ),
                std::make_pair ( 'G', 3 ),
                std::make_pair ( 'H', 3 ),
                std::make_pair ( 'I', 3 ),
                std::make_pair ( 'J', 3 ),
                std::make_pair ( 'K', 3 ),
                std::make_pair ( 'L', 1 ),
                std::make_pair ( 'M', 1 ),
                std::make_pair ( 'N', 3 ),
                std::make_pair ( 'O', 3 ),
                std::make_pair ( 'P', 4 ),
                std::make_pair ( 'Q', 4 ),
                std::make_pair ( 'R', 4 ),
                std::make_pair ( 'S', 4 ),
                std::make_pair ( 'T', 4 ),
                std::make_pair ( 'V', 4 ),
                std::make_pair ( 'U', 4 ),
                std::make_pair ( 'W', 4 ),
                std::make_pair ( 'X', 4 ),
                std::make_pair ( 'Y', 4 ),
                std::make_pair ( 'Z', 2 ), };
    result.clear();
    algorithm ( adjacency_lists, result, 'E' );
    std::cout << "test #3: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    answer.clear();
    answer = {
                std::make_pair ( 'A', 2 ),
                std::make_pair ( 'B', 3 ),
                std::make_pair ( 'C', 1 ),
                std::make_pair ( 'D', 3 ),
                std::make_pair ( 'E', 3 ),
                std::make_pair ( 'F', 3 ),
                std::make_pair ( 'G', 4 ),
                std::make_pair ( 'H', 4 ),
                std::make_pair ( 'I', 2 ),
                std::make_pair ( 'J', 0 ),
                std::make_pair ( 'K', 4 ),
                std::make_pair ( 'L', 4 ),
                std::make_pair ( 'M', 4 ),
                std::make_pair ( 'N', 4 ),
                std::make_pair ( 'O', 4 ),
                std::make_pair ( 'P', 5 ),
                std::make_pair ( 'Q', 5 ),
                std::make_pair ( 'R', 5 ),
                std::make_pair ( 'S', 5 ),
                std::make_pair ( 'T', 3 ),
                std::make_pair ( 'V', 3 ),
                std::make_pair ( 'U', 1 ),
                std::make_pair ( 'W', 1 ),
                std::make_pair ( 'X', 5 ),
                std::make_pair ( 'Y', 5 ),
                std::make_pair ( 'Z', 5 ), };
    result.clear();
    algorithm ( adjacency_lists, result, 'J' );
    std::cout << "test #4: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';
}
