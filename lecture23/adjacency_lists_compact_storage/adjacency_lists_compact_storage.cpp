#include "adjacency_lists_compact_storage.h"

void adjacency_lists_compact_storage ( const std::vector < char > &vertexes,
                                       const std::vector < std::vector < char > > &lists,
                                       std::vector < char > &vertexesOut,
                                       std::vector < char > &listsOut,
                                       std::vector < int > &indexesOut )
{
    indexesOut.push_back ( 0 );
    for ( std::size_t index = 0; index < vertexes.size(); ++index )
    {
        vertexesOut.push_back ( vertexes[index] );
        indexesOut.push_back ( indexesOut[index]
                               + static_cast < signed > ( lists[index].size() ) );

        for ( const auto &neighbor : lists[index] )
            listsOut.push_back ( neighbor );
    }
}
