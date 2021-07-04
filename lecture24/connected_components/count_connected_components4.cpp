#include "count_connected_components4.h"

namespace Count_connected_components4 {
    void depth_first_search(Vertex_t start, const Lists_t& G, Vertexes_t& used) {
        used.insert(start);

        for (Vertex_t neighbor : G.at(start)) {
            if (used.find(neighbor) == used.cend()) {
                depth_first_search(neighbor, G, used);
            }
        }
    }
}

int count_connected_components4(const Lists_t& G)
{
    Vertexes_t used;
    int counter = 0;

    for (const auto& vn : G) {
        if (used.find(vn.first) == used.cend()) {
            Count_connected_components4::depth_first_search(vn.first, G, used);
            ++counter;
        }
    }

    return counter;
}
