#include "floyd_uolsher4.h"

namespace Floyd_uolsher4 {
    int calculate_unreacheble_maximum(const Lists3_t& G) {
        int maximum = 0;

        for (const auto& vn : G)
            for (const auto& v : vn.second)
                maximum += v.second;

        return 10 * maximum;
    }

    int minimum(int a, int b) {
        return a < b ? a : b;
    }
}

void floyd_uolsher4(const Lists3_t& G, All_distances3_t& d_out) {
    Vertexes_vector_t v;
    v.resize(G.size() + 1);

    std::size_t index = 1;

    for (const auto& vn : G) {
        v[index] = vn.first;
        ++index;
    }

    int unreachable_maximum = Floyd_uolsher4::calculate_unreacheble_maximum(G);
    All_distances3_t F0;

    for (const auto& vn1 : G) {
        Distances3_t d;

        for (const auto& vn2 : G) {
            int distance = unreachable_maximum;

            if (vn1.second.find(vn2.first) != vn1.second.cend())
                distance = vn1.second.at(vn2.first);
            else if (vn2.first == vn1.first)
                distance = 0;
            
            d.insert(std::pair<Vertex3_t, int>(vn2.first, distance));
        }

        F0.insert(std::pair<Vertex3_t, Distances3_t>(vn1.first, d));
    }

    All_distances3_t F[2];
    F[0] = F0;
    F[1] = F0;

    for (int k = 1; k < G.size() + 1; ++k)
        for (int i = 1; i < G.size() + 1; ++i)
            for (int j = 1; j < G.size() + 1; ++j)
                F[k % 2][v[i]][v[j]] = Floyd_uolsher4::minimum(F[(k - 1) % 2][v[i]][v[j]],
                    F[(k - 1) % 2][v[i]][v[k]] + F[(k - 1) % 2][v[k]][v[j]]);

    d_out = F[G.size() % 2];
}
