#ifndef TEST_ADJACENCY_LISTS_COMPACT_STORAGE_H
#define TEST_ADJACENCY_LISTS_COMPACT_STORAGE_H


#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <vector>

void test_adjacency_lists_compact_storage ( void ( *algorithm )( const std::vector < char > &vertexes,
                                                                 const std::vector < std::vector < char > > &lists,
                                                                 std::vector < char > &vertexesOut,
                                                                 std::vector < char > &listsOut,
                                                                 std::vector < int > &indexesOut ) );


#endif // TEST_ADJACENCY_LISTS_COMPACT_STORAGE_H
