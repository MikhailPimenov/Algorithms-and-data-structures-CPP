#include "count_connected_components3.h"
void depth_first_search3(const Lists_t& g, Vertex_t start, Vertexes_t &used) {
    used.insert(start);

    for (Vertex_t neighbor : g.at(start))
        if (used.find(neighbor) == used.cend())
            depth_first_search3(g, neighbor, used);
}

int count_connected_components3(const Lists_t& g)
{
    Vertexes_t used;
    int counter = 0;

    for (const auto& vn : g) {
        if (used.find(vn.first) == used.cend()) {
            ++counter;
            depth_first_search3(g, vn.first, used);
        }
    }

    return counter;
}
