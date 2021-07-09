#include "adjacency_matrix4.h"

namespace Adjacency_matrix4 {
    int find(const char* source, int length, char item) {
        for (int i = 0; i < length; ++i)
            if (source[i] == item)
                return i;
        return -1;
    }
}

int adjacency_matrix4(int*& matrix_out, char*& vertexes_out, int*& indexes_out) {
    std::cout << "Enter the number of vertexes:";
    int n = 0;
    std::cin >> n;
    
    std::cout << "Enter the number of edges:";
    int m = 0;
    std::cin >> m;

    matrix_out = new int[(n + 1) * (n + 1)];
    for (int i = 0; i < (n + 1) * (n + 1); ++i)
        matrix_out[i] = 0;
    
    vertexes_out = new char[n];
    indexes_out = new int[n];
    std::size_t v_index = 0;

    for (int i = 0; i < m; ++i) {
        std::string edge;
        std::cout << "Enter the edge:";
        std::cin >> edge;

        char v1 = edge[0];
        char v2 = edge[1];

        int v1_index_in_vertexes = Adjacency_matrix4::find(vertexes_out, v_index, v1);
        if (v1_index_in_vertexes == -1) {
            vertexes_out[v_index] = v1;
            indexes_out[v_index] = v_index + 1;
            v1_index_in_vertexes = v_index;
            ++v_index;
        }

        int v2_index_in_vertexes = Adjacency_matrix4::find(vertexes_out, v_index, v2);
        if (v2_index_in_vertexes == -1) {
            vertexes_out[v_index] = v2;
            indexes_out[v_index] = v_index + 1;
            v2_index_in_vertexes = v_index;
            ++v_index;
        }

        int v1_index = indexes_out[v1_index_in_vertexes];
        int v2_index = indexes_out[v2_index_in_vertexes];

        ++(matrix_out[v1_index * (n + 1) + v2_index]);
        ++(matrix_out[v2_index * (n + 1) + v1_index]);
    }
    
    return 0;
}
