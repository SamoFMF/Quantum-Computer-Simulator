#include "matrix.h"
#include <iostream>

/*
Multiplies matrices A and B and saves the result into C.

Inputs:
    -(p x q) matrix A
    -(q x r) matrix B
    -matrix C

Output:
    -(p x r) matrix (saved into C)
*/
void multiply(const matrix &A, const matrix &B, matrix &C) {
    int p = A.size();
    int q = B.size();
    int r = B[0].size();

    C.resize(p);
    double value;
    for (int i = 0; i < p; i++) {
        C[i].resize(r);
        for (int j = 0; j < r; j++) {
            value = 0;
            for (int k = 0; k < q; k++) {
                value += A[i][k] * B[k][j];
            }
            C[i][j] = value;
        }
    }
}

/*
Creates an identity matrix and saves it into M.

Inputs:
    -int nrows: number of rows
    -int ncols: number of columns
    -matrix M

Output:
    -(nrows x ncols) identity matrix (saved into M)
*/
void eye(int nrows, int ncols, matrix &M) {
    M.resize(nrows);
    for (int i = 0; i < nrows; i++) {
        M[i].resize(ncols);
        if (i < ncols) {
            M[i][i] = 1;
        }
    }
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