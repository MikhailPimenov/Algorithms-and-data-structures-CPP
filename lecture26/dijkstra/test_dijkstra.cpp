#include "test_dijkstra.h"

void test_dijkstra ( void ( *algorithm ) ( const Lists3_t &, Vertex3_t start, Distances3_t & ) )
{
    std::cout << "test_dijkstra:\n";
    Lists3_t adjacency_lists =
    {
    std::make_pair ( 'A', Vertexes3_t { std::make_pair ('B', 2),
                                        std::make_pair ('H', 15) } ),
    std::make_pair ( 'B', Vertexes3_t { std::make_pair ('A', 2),
                                        std::make_pair ('C', 1),
                                        std::make_pair ('D', 5) } ),
    std::make_pair ( 'C', Vertexes3_t { std::make_pair ('B', 1),
                                        std::make_pair ('D', 3),
                                        std::make_pair ('F', 2),
                                        std::make_pair ('G', 1) } ),
    std::make_pair ( 'D', Vertexes3_t { std::make_pair ('B', 5),
                                        std::make_pair ('C', 3),
                                        std::make_pair ('F', 4),
                                        std::make_pair ('E', 6) } ),
    std::make_pair ( 'E', Vertexes3_t { std::make_pair ('D', 6),
                                        std::make_pair ('F', 7),
                                        std::make_pair ('I', 2) } ),
    std::make_pair ( 'F', Vertexes3_t { std::make_pair ('C', 2),
                                        std::make_pair ('D', 4),
                                        std::make_pair ('E', 7),
                                        std::make_pair ('G', 1),
                                        std::make_pair ('H', 3) } ),
    std::make_pair ( 'G', Vertexes3_t { std::make_pair ('C', 1),
                                        std::make_pair ('F', 1) } ),
    std::make_pair ( 'H', Vertexes3_t { std::make_pair ('A', 15),
                                        std::make_pair ('F', 3),
                                        std::make_pair ('I', 12) } ),
    std::make_pair ( 'I', Vertexes3_t { std::make_pair ('E', 2),
                                        std::make_pair ('H', 12), } ),
    };

    Vertex3_t start = 'A';

    Distances3_t answer =
    {
        std::make_pair ('A', 0),
        std::make_pair ('B', 2),
        std::make_pair ('C', 3),
        std::make_pair ('D', 6),
        std::make_pair ('E', 12),
        std::make_pair ('F', 5),
        std::make_pair ('G', 4),
        std::make_pair ('H', 8),
        std::make_pair ('I', 14),
    };
    Distances3_t result;
    algorithm ( adjacency_lists, start, result );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    adjacency_lists.clear();
    adjacency_lists =
    {
    std::make_pair ( 'A', Vertexes3_t { std::make_pair ('B', 2),
                                        std::make_pair ('H', 15) } ),
    std::make_pair ( 'B', Vertexes3_t { std::make_pair ('A', 2),
                                        std::make_pair ('C', 1),
                                        std::make_pair ('D', 5) } ),
    std::make_pair ( 'C', Vertexes3_t { std::make_pair ('B', 1),
                                        std::make_pair ('D', 3),
                                        std::make_pair ('F', 2),
                                        std::make_pair ('G', 1) } ),
    std::make_pair ( 'D', Vertexes3_t { std::make_pair ('B', 5),
                                        std::make_pair ('C', 3),
                                        std::make_pair ('F', 4),
                                        std::make_pair ('E', 6) } ),
    std::make_pair ( 'E', Vertexes3_t { std::make_pair ('D', 6),
                                        std::make_pair ('F', 7),
                                        std::make_pair ('I', 2) } ),
    std::make_pair ( 'F', Vertexes3_t { std::make_pair ('C', 2),
                                        std::make_pair ('D', 4),
                                        std::make_pair ('E', 7),
                                        std::make_pair ('G', 1),
                                        std::make_pair ('H', 3) } ),
    std::make_pair ( 'G', Vertexes3_t { std::make_pair ('C', 1),
                                        std::make_pair ('F', 1) } ),
    std::make_pair ( 'H', Vertexes3_t { std::make_pair ('A', 15),
                                        std::make_pair ('F', 3),
                                        std::make_pair ('I', 12) } ),
    std::make_pair ( 'I', Vertexes3_t { std::make_pair ('E', 2),
                                        std::make_pair ('H', 12), } ),
    std::make_pair ( 'J', Vertexes3_t { std::make_pair ('K', 2) } ),
    std::make_pair ( 'K', Vertexes3_t { std::make_pair ('J', 2) } ),
    };

    start = 'A';

    answer.clear();
    answer =
    {
        std::make_pair ('A', 0),
        std::make_pair ('B', 2),
        std::make_pair ('C', 3),
        std::make_pair ('D', 6),
        std::make_pair ('E', 12),
        std::make_pair ('F', 5),
        std::make_pair ('G', 4),
        std::make_pair ('H', 8),
        std::make_pair ('I', 14),
    };

    int max = 0;
    for ( const auto &vertex_and_neighbours : adjacency_lists )
        for ( const auto &neighbor_and_weight : adjacency_lists.at ( vertex_and_neighbours.first ) )
            max += neighbor_and_weight.second;
    max *= 5;
    result.clear();
    algorithm ( adjacency_lists, start, result );
    int max_resultJ = result.at ( 'J' ); result.erase ( result.find ( 'J' ) );
    int max_resultK = result.at ( 'K' ); result.erase ( result.find ( 'K' ) );

    std::cout << "test #2: " << ( ( ( answer == result )
                                    && ( max_resultJ >= max )
                                    && ( max_resultK >= max ) ) ? "ok" : "FAILED" ) << '\n';



    adjacency_lists.clear();
    adjacency_lists =
    {
    std::make_pair ( 'A', Vertexes3_t { std::make_pair ('B', 2),
                                        std::make_pair ('H', 15) } ),
    std::make_pair ( 'B', Vertexes3_t { std::make_pair ('A', 2),
                                        std::make_pair ('C', 1),
                                        std::make_pair ('D', 5) } ),
    std::make_pair ( 'C', Vertexes3_t { std::make_pair ('B', 1),
                                        std::make_pair ('D', 3),
                                        std::make_pair ('F', 2),
                                        std::make_pair ('G', 1) } ),
    std::make_pair ( 'D', Vertexes3_t { std::make_pair ('B', 5),
                                        std::make_pair ('C', 3),
                                        std::make_pair ('F', 4),
                                        std::make_pair ('E', 6) } ),
    std::make_pair ( 'E', Vertexes3_t { std::make_pair ('D', 6),
                                        std::make_pair ('F', 7),
                                        std::make_pair ('I', 2) } ),
    std::make_pair ( 'F', Vertexes3_t { std::make_pair ('C', 2),
                                        std::make_pair ('D', 4),
                                        std::make_pair ('E', 7),
                                        std::make_pair ('G', 1),
                                        std::make_pair ('H', 3) } ),
    std::make_pair ( 'G', Vertexes3_t { std::make_pair ('C', 1),
                                        std::make_pair ('F', 1) } ),
    std::make_pair ( 'H', Vertexes3_t { std::make_pair ('A', 15),
                                        std::make_pair ('F', 3),
                                        std::make_pair ('I', 12) } ),
    std::make_pair ( 'I', Vertexes3_t { std::make_pair ('E', 2),
                                        std::make_pair ('H', 12), } ),
    };

    start = 'E';

    answer.clear();
    answer =
    {
        std::make_pair ('A', 12),
        std::make_pair ('B', 10),
        std::make_pair ('C', 9),
        std::make_pair ('D', 6),
        std::make_pair ('E', 0),
        std::make_pair ('F', 7),
        std::make_pair ('G', 8),
        std::make_pair ('H', 10),
        std::make_pair ('I', 2),
    };
    result.clear();
    algorithm ( adjacency_lists, start, result );
    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    adjacency_lists.clear();
    adjacency_lists =
    {
    std::make_pair ( 'A', Vertexes3_t { std::make_pair ('B', 2),
                                        std::make_pair ('H', 15) } ),
    std::make_pair ( 'B', Vertexes3_t { std::make_pair ('A', 2),
                                        std::make_pair ('C', 1),
                                        std::make_pair ('D', 5) } ),
    std::make_pair ( 'C', Vertexes3_t { std::make_pair ('B', 1),
                                        std::make_pair ('D', 3),
                                        std::make_pair ('F', 2),
                                        std::make_pair ('G', 1) } ),
    std::make_pair ( 'D', Vertexes3_t { std::make_pair ('B', 5),
                                        std::make_pair ('C', 3),
                                        std::make_pair ('F', 4),
                                        std::make_pair ('E', 6) } ),
    std::make_pair ( 'E', Vertexes3_t { std::make_pair ('D', 6),
                                        std::make_pair ('F', 7),
                                        std::make_pair ('I', 2) } ),
    std::make_pair ( 'F', Vertexes3_t { std::make_pair ('C', 2),
                                        std::make_pair ('D', 4),
                                        std::make_pair ('E', 7),
                                        std::make_pair ('G', 1),
                                        std::make_pair ('H', 3) } ),
    std::make_pair ( 'G', Vertexes3_t { std::make_pair ('C', 1),
                                        std::make_pair ('F', 1) } ),
    std::make_pair ( 'H', Vertexes3_t { std::make_pair ('A', 15),
                                        std::make_pair ('F', 3),
                                        std::make_pair ('I', 12) } ),
    std::make_pair ( 'I', Vertexes3_t { std::make_pair ('E', 2),
                                        std::make_pair ('H', 12), } ),
    };

    start = 'C';

    answer.clear();
    answer =
    {
        std::make_pair ('A', 3),
        std::make_pair ('B', 1),
        std::make_pair ('C', 0),
        std::make_pair ('D', 3),
        std::make_pair ('E', 9),
        std::make_pair ('F', 2),
        std::make_pair ('G', 1),
        std::make_pair ('H', 5),
        std::make_pair ('I', 11),
    };
    result.clear();
    algorithm ( adjacency_lists, start, result );
    std::cout << "test #4: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

}
