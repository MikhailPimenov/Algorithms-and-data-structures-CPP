#include "distances.h"



void distances ( const Lists_t &adjacency_lists, Distances_t &distancesOut, Vertex_t start )
{
    for ( const auto &vertex_and_neighbours : adjacency_lists )
        distancesOut.insert ( std::make_pair ( vertex_and_neighbours.first, -1 ) );
    distancesOut.at ( start ) = 0;

    Queue_t queue;
    queue.push ( start );

    while ( ! queue.empty() )
    {
        Vertex_t current_vertex = queue.front();
        queue.pop();

        for ( const auto neighbor : adjacency_lists.at ( current_vertex ) )
        {
            if ( distancesOut.at ( neighbor ) == -1 )
            {
                distancesOut.at ( neighbor ) = 1 + distancesOut.at ( current_vertex );
                queue.push ( neighbor );
            }
        }
    }

}
