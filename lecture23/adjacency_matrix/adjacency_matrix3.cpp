#include "adjacency_matrix3.h"

namespace Adjacency_matrix3 {
    int find(const char *string, int length, char symbol) {
        for (int i = 0; i < length; ++i)
            if (string[i] == symbol)
                return i;
        return -1;
    }
}

int adjacency_matrix3(int*& m, char*& v, int*& i)
{
    std::cout << "Enter the number of vertexes: ";
    int n;
    std::cin >> n;

    std::cout << "Enter the number of edges: ";
    int k;
    std::cin >> k;


    m = new int[(n + 1) * (n + 1)];
    int** mm = new int* [n + 1];
    for (int j = 0; j < n + 1; ++j)
        mm[j] = m + j * (n + 1);

    for (int j = 0; j < n + 1; ++j)
        for (int w = 0; w < n + 1; ++w)
            mm[j][w] = 0;

    v = new char[n];
    i = new int[n];
    int length = 0;

    for (int j = 0; j < k; ++j) {
        std::cout << "Enter the edge:\n";
        std::string edge;
        std::cin >> edge;

        int i0 = -1;
        int i1 = -1;

        
        i0 = Adjacency_matrix3::find(v, length, edge[0]);
        if (i0 == -1) {
            v[length] = edge[0];
            i0 = length;
            i[i0] = i0 + 1;
            ++length;
        }
        i1 = Adjacency_matrix3::find(v, length, edge[1]);
        if (i1 == -1) {
            v[length] = edge[1];
            i1 = length;
            i[i1] = i1 + 1;
            ++length;
        }

        ++mm[i[i1]][i[i0]];
        ++mm[i[i0]][i[i1]];

    }

    delete[]mm;

    return 0;
}
