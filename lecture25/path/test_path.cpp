#include "test_path.h"

void test_path ( void ( *algorithm ) ( const Lists_t &, Path_t &, Vertex_t, Vertex_t ) )
{
    std::cout << "test_path:\n";

    Lists_t adjacency_lists = {
                std::make_pair ( 'A', Vertexes_t {'F', 'N', 'B', 'G', 'D', 'J'} ),
                std::make_pair ( 'B', Vertexes_t {'A', 'H', 'P'} ),
                std::make_pair ( 'C', Vertexes_t {'H', 'M'} ),
                std::make_pair ( 'D', Vertexes_t {'A', 'J', 'G'} ),
                std::make_pair ( 'E', Vertexes_t {'J', 'K'} ),
                std::make_pair ( 'F', Vertexes_t {'A', 'F', 'I'} ),
                std::make_pair ( 'G', Vertexes_t {'A', 'D', 'L', 'M'} ),
                std::make_pair ( 'H', Vertexes_t {'B', 'C'} ),
                std::make_pair ( 'I', Vertexes_t {'U', 'F'} ),
                std::make_pair ( 'J', Vertexes_t {'E', 'F', 'D'} ),
                std::make_pair ( 'K', Vertexes_t {'E'} ),
                std::make_pair ( 'L', Vertexes_t {'G'} ),
                std::make_pair ( 'M', Vertexes_t {'G', 'C'} ),
                std::make_pair ( 'N', Vertexes_t {'A', 'O'} ),
                std::make_pair ( 'O', Vertexes_t {'N', 'T'} ),
                std::make_pair ( 'P', Vertexes_t {'B', 'V'} ),
                std::make_pair ( 'Q', Vertexes_t {'U', 'S'} ),
                std::make_pair ( 'R', Vertexes_t {'T', 'V'} ),
                std::make_pair ( 'S', Vertexes_t {'Q', 'T'} ),
                std::make_pair ( 'T', Vertexes_t {'S', 'R', 'O'} ),
                std::make_pair ( 'U', Vertexes_t {'I', 'Q'} ),
                std::make_pair ( 'V', Vertexes_t {'R', 'P'} ),
    };
    Path_t answer = { 'G', 'D', 'J' };
    Path_t result;

    algorithm ( adjacency_lists, result, 'G', 'J' );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';
    answer.clear();
    result.clear();


    answer = { 'A', 'N', 'O', 'T' };
    algorithm ( adjacency_lists, result, 'A','T' );
    std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';
    answer.clear();
    result.clear();


    answer = { 'G', 'A', 'B' };
    algorithm ( adjacency_lists, result, 'G','B' );
    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';
    answer.clear();
    result.clear();
}
