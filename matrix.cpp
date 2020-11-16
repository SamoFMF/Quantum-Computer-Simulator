#include "matrix.h"
#include <iostream>

/*
Multiplies matrices A and B.

Inputs:
    -(p x q) matrix A
    -(q x r) matrix B
    -matrix C

Output:
    -(p x r) matrix C
*/
matrix multiply(const matrix &A, const matrix &B) {
    int p = A.size();
    int q = B.size();
    int r = B[0].size();

    matrix C(p, vector<double>(r, 0));

    double value;
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            value = 0;
            for (int k = 0; k < q; k++) {
                value += A[i][k] * B[k][j];
            }
            C[i][j] = value;
        }
    }
    return C;
}

/*
Creates an identity matrix.

Inputs:
    -int nrows: number of rows
    -int ncols: number of columns

Output:
    -(nrows x ncols) identity matrix M
*/
matrix eye(int nrows, int ncols) {
    matrix M(nrows, vector<double>(ncols, 0));
    for (int i = 0; i < nrows; i++) {
        if (i < ncols) {
            M[i][i] = 1;
        }
    }
    return M;
}

/*
Prints matrix to standard output.

Inputs:
    -matrix A
*/
void print(const matrix &M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[i].size(); j++) {
            cout << M[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << endl;
}