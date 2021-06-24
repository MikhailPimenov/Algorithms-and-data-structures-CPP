#include "dijkstra.h"

int calculate_unreachable_distance ( const Lists3_t &adjacency_lists )
{
    int result = 0;

    for ( const auto &vertex_and_neighbours : adjacency_lists )
        for ( const auto &neighbor_and_weight : adjacency_lists.at ( vertex_and_neighbours.first ) )
            result += neighbor_and_weight.second;

    return result * 5;
}
void set_distances ( const Lists3_t &adjacency_lists, int unreachable_distance, Vertex3_t start, Distances3_t &distancesOut )
{
    for ( const auto &vertex_and_neighbours : adjacency_lists )
        distancesOut.insert ( std::make_pair ( vertex_and_neighbours.first, unreachable_distance ) );
    distancesOut.at ( start ) = 0;
}
void calculate_distances ( const Lists3_t &adjacency_lists, Vertex3_t start, Distances3_t &distancesOut )
{
    Queue3_t queue;
    queue.push ( start );

    while ( ! queue.empty() )
    {
        Vertex3_t current_vertex = queue.front();
        queue.pop();

        for ( const auto &neighbor_and_weight : adjacency_lists.at ( current_vertex ) )
        {
            auto old_distance = distancesOut.at ( neighbor_and_weight.first );
            auto new_distance = distancesOut.at ( current_vertex ) + neighbor_and_weight.second;
            if (  new_distance < old_distance )
            {
                distancesOut.at ( neighbor_and_weight.first ) = new_distance;
                queue.push ( neighbor_and_weight.first );
            }
        }
    }
}
void  dijkstra ( const Lists3_t &adjacency_lists, Vertex3_t start, Distances3_t &distancesOut )
{
    int unreachable_distance = calculate_unreachable_distance ( adjacency_lists );

    set_distances ( adjacency_lists, unreachable_distance, start, distancesOut );

    calculate_distances ( adjacency_lists, start, distancesOut );
}
