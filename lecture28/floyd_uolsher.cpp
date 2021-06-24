#include "floyd_uolsher.h"

int calculate_unreachable_maximum ( const Lists3_t &adjacency_lists )
{
    int result = 0;
    for ( const auto &vertex_and_neighbours : adjacency_lists )
        for ( const auto &neighbor_and_weight : vertex_and_neighbours.second )
            result += neighbor_and_weight.second;

    return 1000 * result;
}
void init_distances ( const Lists3_t &graph, All_distances3_t &out )
{
    int unreachable_maximum = calculate_unreachable_maximum ( graph );
    out.reserve ( graph.size() );

    for ( const auto &vertex_and_neighbours : graph )
        out.insert ( std::make_pair ( vertex_and_neighbours.first, Distances3_t {} ) );

    for ( const auto &vertex_and_neighbours_i : graph )
    {
        for ( const auto &vertex_and_neighbours_j : graph )
        {
            auto &i_first = vertex_and_neighbours_i.first;
            auto &j_first = vertex_and_neighbours_j.first;
            if ( i_first == j_first )
            {
                out.at ( i_first ).insert ( std::make_pair ( j_first, 0 ) );
                out.at ( j_first ).insert ( std::make_pair ( i_first, 0 ) );
            }
            if ( graph.at ( i_first ).find ( j_first ) == graph.at ( i_first ).cend() )
                out.at ( i_first ).insert ( std::make_pair ( j_first, unreachable_maximum ) );
            else
                out.at ( i_first ).insert ( std::make_pair ( j_first, graph.at ( i_first ).at ( j_first ) ) );

            if ( graph.at ( j_first ).find ( i_first ) == graph.at ( j_first ).cend() )
                out.at ( j_first ).insert ( std::make_pair ( i_first, unreachable_maximum ) );
            else
                out.at ( j_first ).insert ( std::make_pair ( i_first, graph.at ( j_first ).at ( i_first ) ) );
        }
    }
    return;
}
void find_distances ( const Lists3_t &graph, All_distances3_t &out )
{
    std::vector < Vertex3_t > vertexes;
    vertexes.reserve ( graph.size() );
    for ( const auto &vertex_and_neighbours : graph )
        vertexes.push_back ( vertex_and_neighbours.first );


    All_distances3_t buffers[2] = { out, out };
    for ( std::size_t k = 0; k < vertexes.size(); ++k )
    {
        for ( const auto &v_i : graph )
        {
            for ( const auto &v_j : graph )
            {
                buffers[k % 2].at ( v_i.first ).at ( v_j.first ) = Common::min (
                            buffers[( k - 1 ) % 2].at ( v_i.first ).at ( v_j.first ),
                            buffers[( k - 1 ) % 2].at ( v_i.first ).at ( vertexes.at ( k ) )
                          + buffers[( k - 1 ) % 2].at ( vertexes.at ( k ) ).at ( v_j.first ) );
            }
        }
    }
    out = buffers[( vertexes.size() - 1 ) % 2];
}
void floyd_uolsher ( const Lists3_t &adjacency_lists, All_distances3_t &all_distancesOut )
{
    init_distances ( adjacency_lists, all_distancesOut );

    find_distances ( adjacency_lists, all_distancesOut );
}
