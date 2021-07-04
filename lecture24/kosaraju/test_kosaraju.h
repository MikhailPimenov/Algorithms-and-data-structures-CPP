#ifndef TEST_KOSARAJU_H
#define TEST_KOSARAJU_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "../Types_for_graph.h"

void test_reverse_graph ( void ( *algorithm ) ( const Lists_t &adjacency_lists,
                                                Lists_t &reversed_adjacency_listsOut ) );

void test_kosaraju ( int ( *algorithm ) ( const Lists_t &adjacency_lists, Components_t &components_out ) );


#endif // TEST_KOSARAJU_H
