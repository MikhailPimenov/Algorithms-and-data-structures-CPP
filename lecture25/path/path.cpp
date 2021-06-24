#include "path.h"

void find_distances ( const Lists_t &adjacency_lists, Vertex_t start, Vertex_t finish, Distances_t &distancesOut )
{
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
                distancesOut.at ( neighbor ) = distancesOut.at ( current_vertex ) + 1;
                if ( neighbor == finish )
                    break;

                queue.push ( neighbor );
            }
        }
    }
}
void reveal_path ( const Lists_t &adjacency_lists, Vertex_t start, Vertex_t finish, const Distances_t &distances, Path_t &reversed_pathOut )
{
    Vertex_t current_vertex = finish;
    reversed_pathOut.push_back ( finish );

    while ( current_vertex != start )
    {
        for ( const auto neighbor : adjacency_lists.at ( current_vertex ) )
        {
            if ( distances.at ( neighbor ) == distances.at ( current_vertex ) - 1 )
            {
                reversed_pathOut.push_back ( neighbor );
                current_vertex = neighbor;
                break;
            }
        }
    }
}
void create_distances ( const Lists_t &adjacency_lists, Vertex_t start, Distances_t &distancesOut )
{
    for ( const auto &vertex_and_neighbours : adjacency_lists )
        distancesOut.insert ( std::make_pair ( vertex_and_neighbours.first, -1 ) );
    distancesOut.at ( start ) = 0;
}
void path ( const Lists_t &adjacency_lists, Path_t &pathOut, Vertex_t start, Vertex_t finish )
{
    Distances_t distances;
    create_distances ( adjacency_lists, start, distances );

    find_distances ( adjacency_lists, start, finish, distances );

    Path_t reversed_path;
    reveal_path ( adjacency_lists, start, finish, distances, reversed_path );

    pathOut.assign ( reversed_path.crbegin(), reversed_path.crend() );
}
