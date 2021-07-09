#include "chess_queen4.h"

int chess_queen4(int m, int n) {
    int* f = new int[m * n];
    int** ff = new int* [m];
    for (int i = 0; i < m; ++i) {
        ff[i] = f + i * n;
    }
    for (int i = 0; i < m; ++i) {
        ff[i][0] = 1;
    }
    for (int j = 0; j < n; ++j) {
        ff[0][j] = 1;
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            ff[i][j] = ff[i - 1][j] + ff[i][j - 1];
        }
    }
    
    int result = ff[m - 1][n - 1];
    
    delete[] ff;
    delete[] f;

    return result;
}
