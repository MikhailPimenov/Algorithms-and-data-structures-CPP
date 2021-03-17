#include "test_adjacency_lists_compact_storage.h"

void test_adjacency_lists_compact_storage ( void ( *algorithm )( const std::vector < char > &vertexes,
                                                                 const std::vector < std::vector < char > > &lists,
                                                                 std::vector < char > &vertexesOut,
                                                                 std::vector < char > &listsOut,
                                                                 std::vector < int > &indexesOut ) )
{
    std::cout << "test_adjacency_lists_compact_storage:\n";
    std::vector < char > vertexes { 'A', 'B', 'C', 'D' };
    std::vector < std::vector < char > > lists
    {
        std::vector < char > {'B', 'D'},
        std::vector < char > {'A', 'D', 'C'},
        std::vector < char > {'B', 'D'},
        std::vector < char > {'A', 'B', 'C'},
    };

    std::vector < char > vertexes_result;
    std::vector < int > indexes_result;
    std::vector < char > lists_compact_result;

    std::vector < int > indexes { 0, 2, 5, 7, 10 };
    std::vector < char > lists_compact { 'B', 'D', 'A', 'D', 'C', 'B', 'D', 'A', 'B', 'C' };

    algorithm ( vertexes, lists, vertexes_result, lists_compact_result, indexes_result );

    std::cout << "test #1: " << ( ( vertexes_result == vertexes
                                    && lists_compact_result == lists_compact
                                    && indexes_result == indexes ) ? "ok" : "FAILED" ) << '\n';
}
