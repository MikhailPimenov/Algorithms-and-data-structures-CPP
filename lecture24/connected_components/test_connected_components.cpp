#include "test_connected_components.h"

void test_connected_components ( int ( *algorithm ) ( const Lists_t &adjacency_lists ) )
{
    std::cout << "test_connected_components:\n";

    Lists_t adjacency_lists
    {
        std::make_pair ( 'A', Vertexes_t{} ),
        std::make_pair ( 'B', Vertexes_t{} ),
        std::make_pair ( 'C', Vertexes_t{} ),
        std::make_pair ( 'D', Vertexes_t{} ),
    };
    int answer = 4;
    int result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #1: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'A' } ),
        std::make_pair ( 'C', Vertexes_t{} ),
        std::make_pair ( 'D', Vertexes_t{} ),
    };
    answer = 3;
    result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #2: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'A' } ),
        std::make_pair ( 'C', Vertexes_t { 'D' } ),
        std::make_pair ( 'D', Vertexes_t { 'C' } ),
    };
    answer = 2;
    result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #3: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B', 'C', 'D' } ),
        std::make_pair ( 'B', Vertexes_t { 'A', 'C', 'D' } ),
        std::make_pair ( 'C', Vertexes_t { 'D', 'A', 'B' } ),
        std::make_pair ( 'D', Vertexes_t { 'C', 'A', 'B' } ),
    };
    answer = 1;
    result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #4: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';


}
