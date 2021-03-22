#include "test_kosaraju.h"

void test_reverse_graph ( void ( *algorithm ) ( const Lists_t &adjacency_lists,
                                                Lists_t &reversed_adjacency_listsOut ) )
{
    std::cout << "test_reverse_graph:\n";

    Lists_t adjacency_lists
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'C' } ),
        std::make_pair ( 'C', Vertexes_t { 'D' } ),
        std::make_pair ( 'D', Vertexes_t { 'A' } ),
    };
    Lists_t answer
    {
        std::make_pair ( 'A', Vertexes_t { 'D' } ),
        std::make_pair ( 'B', Vertexes_t { 'A' } ),
        std::make_pair ( 'C', Vertexes_t { 'B' } ),
        std::make_pair ( 'D', Vertexes_t { 'C' } ),
    };
    Lists_t result;
    algorithm ( adjacency_lists, result );
    std::cout << "test #1: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';
    adjacency_lists.clear();
    result.clear();
    answer.clear();

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'C' } ),
        std::make_pair ( 'C', Vertexes_t { 'D', 'E' } ),
        std::make_pair ( 'D', Vertexes_t{} ),
        std::make_pair ( 'E', Vertexes_t { 'A', 'D' } ),
    };
    answer =
    {
        std::make_pair ( 'A', Vertexes_t { 'E' } ),
        std::make_pair ( 'B', Vertexes_t { 'A' } ),
        std::make_pair ( 'C', Vertexes_t { 'B' } ),
        std::make_pair ( 'D', Vertexes_t { 'C', 'E' } ),
        std::make_pair ( 'E', Vertexes_t { 'C' } ),
    };

    algorithm ( adjacency_lists, result );
    std::cout << "test #2: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';
    adjacency_lists.clear();
    result.clear();
    answer.clear();

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'C', 'D' } ),
        std::make_pair ( 'C', Vertexes_t { 'A' } ),
        std::make_pair ( 'D', Vertexes_t { 'E' } ),
        std::make_pair ( 'E', Vertexes_t { 'F' } ),
        std::make_pair ( 'F', Vertexes_t { 'D' } ),
        std::make_pair ( 'G', Vertexes_t { 'F', 'H' } ),
        std::make_pair ( 'H', Vertexes_t { 'I' } ),
        std::make_pair ( 'I', Vertexes_t { 'J' } ),
        std::make_pair ( 'J', Vertexes_t { 'G' } ),
        std::make_pair ( 'K', Vertexes_t { 'J' } ),
    };
    answer =
    {
        std::make_pair ( 'A', Vertexes_t { 'C' } ),
        std::make_pair ( 'B', Vertexes_t { 'A' } ),
        std::make_pair ( 'C', Vertexes_t { 'B' } ),
        std::make_pair ( 'D', Vertexes_t { 'B', 'F' } ),
        std::make_pair ( 'E', Vertexes_t { 'D' } ),
        std::make_pair ( 'F', Vertexes_t { 'E', 'G' } ),
        std::make_pair ( 'G', Vertexes_t { 'J' } ),
        std::make_pair ( 'H', Vertexes_t { 'G' } ),
        std::make_pair ( 'I', Vertexes_t { 'H' } ),
        std::make_pair ( 'J', Vertexes_t { 'I', 'K' } ),
        std::make_pair ( 'K', Vertexes_t{} ),
    };

    algorithm ( adjacency_lists, result );
    std::cout << "test #3: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';
    adjacency_lists.clear();
    result.clear();
    answer.clear();
}
void test_kosaraju ( int ( *algorithm ) ( const Lists_t &adjacency_lists ) )
{
    std::cout << "test_kosaraju:\n";

    Lists_t adjacency_lists
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'C' } ),
        std::make_pair ( 'C', Vertexes_t { 'D' } ),
        std::make_pair ( 'D', Vertexes_t { 'A' } ),
    };
    int answer = 1;
    int result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #1: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'C' } ),
        std::make_pair ( 'C', Vertexes_t { 'D', 'E' } ),
        std::make_pair ( 'D', Vertexes_t{} ),
        std::make_pair ( 'E', Vertexes_t { 'A', 'D' } ),
    };
    answer = 2;
    result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #2: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';

    adjacency_lists =
    {
        std::make_pair ( 'A', Vertexes_t { 'B' } ),
        std::make_pair ( 'B', Vertexes_t { 'C', 'D' } ),
        std::make_pair ( 'C', Vertexes_t { 'A' } ),
        std::make_pair ( 'D', Vertexes_t { 'E' } ),
        std::make_pair ( 'E', Vertexes_t { 'F' } ),
        std::make_pair ( 'F', Vertexes_t { 'D' } ),
        std::make_pair ( 'G', Vertexes_t { 'F', 'H' } ),
        std::make_pair ( 'H', Vertexes_t { 'I' } ),
        std::make_pair ( 'I', Vertexes_t { 'J' } ),
        std::make_pair ( 'J', Vertexes_t { 'G' } ),
        std::make_pair ( 'K', Vertexes_t { 'J' } ),
    };
    answer = 4;
    result = 0;
    result = algorithm ( adjacency_lists );
    std::cout << "test #3: " << ( ( result == answer ) ? "ok" : "FAILED" ) << '\n';


}
