#ifndef ADJACENCY_LISTS_COMPACT_STORAGE_H
#define ADJACENCY_LISTS_COMPACT_STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <vector>

void adjacency_lists_compact_storage ( const std::vector < char > &vertexes,
                                       const std::vector < std::vector < char > > &lists ,
                                       std::vector < char > &vertexesOut,
                                       std::vector < char > &listsOut,
                                       std::vector < int > &indexesOut );



#endif // ADJACENCY_LISTS_COMPACT_STORAGE_H
