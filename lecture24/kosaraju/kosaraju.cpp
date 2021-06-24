#include "kosaraju.h"

void reverse_graph (const Lists_t &adjacency_lists , Lists_t &reversed_adjacency_listsOut )
{
    for ( const auto &vertex : adjacency_lists )
        reversed_adjacency_listsOut.insert ( std::make_pair ( vertex.first, Vertexes_t{} ) );

    for ( const auto &vertex : adjacency_lists )
    {
        for ( const auto &neighbor : vertex.second )
            reversed_adjacency_listsOut.at ( neighbor ).insert ( vertex.first );
    }
}

void depth_first_search_forward ( const Lists_t &adjacency_lists, Vertex_t start, Vertexes_t &gray_and_black, Stack_t &stack, Vertexes_t &component, bool forward = true )
{
    gray_and_black.insert ( start );
    if ( ! forward )
        component.insert ( start );

    for ( const auto &neighbor : adjacency_lists.at ( start ) )
    {
        if ( gray_and_black.find ( neighbor ) == gray_and_black.cend() )
        {
            depth_first_search_forward ( adjacency_lists, neighbor, gray_and_black, stack, component, forward );
            if ( forward )
                stack.push ( neighbor );
        }
    }
}

int kosaraju ( const Lists_t &adjacency_lists )
{
    Lists_t reversed_adjacency_lists;
    Stack_t stack;
    Vertexes_t gray_and_black;

    for ( const auto &vertex_and_neighbors : adjacency_lists )
    {
        if ( gray_and_black.find ( vertex_and_neighbors.first ) == gray_and_black.cend() )
        {
            depth_first_search_forward ( adjacency_lists, vertex_and_neighbors.first, gray_and_black, stack, gray_and_black );
            stack.push ( vertex_and_neighbors.first );
        }
    }

    int result = 0;
    Components_t components;
    reverse_graph ( adjacency_lists, reversed_adjacency_lists );
    gray_and_black.clear();

    while ( ! stack.empty() )
    {
        Vertex_t start = stack.top();
        stack.pop();

        if ( gray_and_black.find ( start ) == gray_and_black.cend() )
        {
            components.insert ( std::make_pair ( result, Vertexes_t{} ) );
            depth_first_search_forward ( reversed_adjacency_lists, start, gray_and_black, stack, components.at ( result ), false );
            ++result;
        }
    }


    return result;
}

