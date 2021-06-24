#include "connected_components.h"

void depth_first_search_forward ( const Lists_t &adjacency_lists, Vertex_t start, Vertexes_t &gray_and_black )
{
    gray_and_black.insert ( start );

    for ( const auto &neighbor : adjacency_lists.at ( start ) )
        if ( gray_and_black.find ( neighbor ) == gray_and_black.cend() )
            depth_first_search_forward ( adjacency_lists, neighbor, gray_and_black );
}
int connected_components ( const Lists_t &adjacency_lists )
{
    Vertexes_t gray_and_black{};
    int result = 0;
    for ( const auto &vertex : adjacency_lists )
    {
        if ( gray_and_black.find ( vertex.first ) == gray_and_black.cend() )
        {
            ++result;
            depth_first_search_forward ( adjacency_lists, vertex.first, gray_and_black );
        }
    }
    return result;
}
