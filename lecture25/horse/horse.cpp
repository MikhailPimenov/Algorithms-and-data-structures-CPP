#include "horse.h"

void create_vertex2 ( int letter, int number, Vertex2_t &vertexOut )
{
    std::string letters = "abcdefgh";
    std::string numbers = "12345678";

    assert ( letter < 8 );
    assert ( number < 8 );
    assert ( number >= 0 );
    assert ( letter >= 0 );

    vertexOut.assign ( std::string ( 1, letters[static_cast < size_t > ( letter )] )
            + std::string ( 1, numbers[static_cast < size_t > ( number )] ) );
}
void add_edge ( Lists2_t &adjacency_lists, const Vertex2_t &v1, const Vertex2_t &v2 )
{
    adjacency_lists.at ( v1 ).insert ( v2 );
    adjacency_lists.at ( v2 ).insert ( v1 );
}
void create_graph ( Lists2_t &adjacency_lists )
{
    for ( int i = 0; i < 8; ++i )
    {
        for ( int j = 0; j < 8; ++j )
        {
            Vertex2_t vertex;
            create_vertex2 ( i, j, vertex );
            adjacency_lists.insert ( std::make_pair ( vertex, Vertexes2_t {} ) );
        }
    }

    for ( int i = 0; i < 8; ++i )
    {
        for ( int j = 0; j < 8; ++j )
        {
            Vertex2_t v1;
            create_vertex2 ( i, j, v1 );
            if ( i + 2 < 8 && i >= 0 && j + 1 < 8 && j >= 0 )
            {
                Vertex2_t v2;
                create_vertex2 ( i + 2, j + 1, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i + 1 < 8 && i >= 0 && j + 2 < 8 && j >= 0 )
            {
                Vertex2_t v2;
                create_vertex2 ( i + 1, j + 2, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i - 2 >= 0 && i < 8 && j + 1 < 8 && j >= 0 )
            {
                Vertex2_t v2;
                create_vertex2 ( i - 2, j + 1, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i - 1 >= 0 && i < 8 && j + 2 < 8 && j >= 0 )
            {
                Vertex2_t v2;
                create_vertex2 ( i - 1, j + 2, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i + 2 < 8 && i >= 0 && j - 1 >= 0 && j < 8 )
            {
                Vertex2_t v2;
                create_vertex2 ( i + 2, j - 1, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i + 1 < 8 && i >= 0 && j - 2 >= 0 && j < 8 )
            {
                Vertex2_t v2;
                create_vertex2 ( i + 1, j - 2, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i - 2 >= 0 && i < 8 && j - 1 >= 0 && j < 8 )
            {
                Vertex2_t v2;
                create_vertex2 ( i - 2, j - 1, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
            if ( i - 1 >= 0 && i < 8 && j - 2 >= 0 && j < 8 )
            {
                Vertex2_t v2;
                create_vertex2 ( i - 1, j - 2, v2 );
                add_edge ( adjacency_lists, v1, v2 );
                add_edge ( adjacency_lists, v2, v1 );
            }
        }
    }
}
void create_distances2 ( const Lists2_t &adjacency_lists, const Vertex2_t &start, Distances2_t &distancesOut )
{
    for ( const auto &vertex_and_neighbors : adjacency_lists )
        distancesOut.insert ( std::make_pair ( vertex_and_neighbors.first, -1 ) );
    distancesOut.at ( start ) = 0;
}
void find_distances2 ( const Lists2_t &adjacency_lists, const Vertex2_t &start, const Vertex2_t &finish, Distances2_t &distancesOut )
{
    Queue2_t queue;
    queue.push ( start );

    while ( ! queue.empty() )
    {
        Vertex2_t current_vertex = queue.front();
        queue.pop();

        for ( const auto &neighbor : adjacency_lists.at ( current_vertex ) )
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
void reveal_path2 ( const Lists2_t &adjacency_lists, const Vertex2_t &start, const Vertex2_t &finish, const Distances2_t &distances, Path2_t &reversed_path )
{
    Vertex2_t current_vertex = finish;

    reversed_path.push_back ( current_vertex );
    while ( current_vertex != start )
    {
        for ( const auto &neighbor : adjacency_lists.at ( current_vertex ) )
        {
            if ( distances.at ( neighbor ) == distances.at ( current_vertex ) - 1 )
            {
                reversed_path.push_back ( neighbor );
                current_vertex = neighbor;
                break;
            }
        }
    }
}

void horse ( Path2_t &pathOut, const Vertex2_t &start, const Vertex2_t &finish )
{
    Lists2_t adjacency_lists;
    create_graph ( adjacency_lists );

    Distances2_t distances;
    create_distances2 ( adjacency_lists, start, distances );

    find_distances2 ( adjacency_lists, start, finish, distances );

    Path2_t reversed_path;
    reveal_path2 ( adjacency_lists, start, finish, distances, reversed_path );

    pathOut.assign ( reversed_path.crbegin(), reversed_path.crend() );
}
