#include "count_connected_components2.h"

void depth_first_search(const Lists_t& graph, Vertex_t start, Vertexes_t& used) {
    used.insert(start);

    for (const auto& neighbour : graph.at(start)) {
        if (used.find(neighbour) == used.cend())
            depth_first_search(graph, neighbour, used);
    }
}
int count_connected_components2(const Lists_t& graph)
{
    int counter = 0;

    Vertexes_t used;

    for (const auto &vertex_and_neighbors : graph){
        if (used.find(vertex_and_neighbors.first) == used.cend()) {
            ++counter;
            depth_first_search(graph, vertex_and_neighbors.first, used);
        }
    }

    return counter;
}
