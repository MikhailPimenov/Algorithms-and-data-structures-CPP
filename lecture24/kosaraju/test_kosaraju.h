#ifndef TEST_KOSARAJU_H
#define TEST_KOSARAJU_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using Vertex_t       = char;
using Vertexes_t    = std::unordered_set < Vertex_t >;
using Lists_t         = std::unordered_map < Vertex_t, Vertexes_t >;

void test_reverse_graph ( void ( *algorithm ) ( const Lists_t &adjacency_lists,
                                                Lists_t &reversed_adjacency_listsOut ) );

void test_kosaraju ( int ( *algorithm ) ( const Lists_t &adjacency_lists ) );


#endif // TEST_KOSARAJU_H
