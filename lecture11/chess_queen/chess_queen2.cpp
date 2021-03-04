#include "chess_queen2.h"

int chess_queen2(int m, int n)
{
    int* f_long = new int[m * n];
    int** f = new int* [n];

    for (int i = 0; i < n; ++i)
        f[i] = f_long + m * i;

    for (int i = 0; i < n; ++i)
        f[i][0] = 1;
    for (int j = 0; j < m; ++j)
        f[0][j] = 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            f[i][j] = f[i][j - 1] + f[i - 1][j];
        }
    }

    int result = f[n - 1][m - 1];
    delete[] f;
    delete[] f_long;

    return result;
}
