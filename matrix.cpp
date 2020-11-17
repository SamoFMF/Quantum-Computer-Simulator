#include "matrix.h"
#include <iostream>

/*
Multiplies matrices A and B.

Inputs:
    -(p x q) matrix A,
    -(q x r) matrix B,

Output:
    -(p x r) product matrix of A and B.
*/
matrix multiply(const matrix &A, const matrix &B) {
    const unsigned int p = A.size();
    const unsigned int q = B.size();
    const unsigned int r = B[0].size();

    matrix C(p, vec(r, 0));

    for (unsigned int i = 0; i < p; i++) {
        for (unsigned int j = 0; j < r; j++) {
            for (int k = 0; k < q; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

/*
Multiplies matrix A and vector u.

Inputs:
    -(p x q) matrix A,
    -vector u of length q.

Output:
    -product of A and u of length p.
*/
vec multiply(const matrix &A, const vec &u) {
    const unsigned int p = A.size();
    const unsigned int q = u.size();

    vec v(p, 0);
    
    for (unsigned int i = 0; i < p; i++) {
        for (unsigned int j = 0; j < q; j++) {
            v[i] += A[i][j] * u[j];
        }
    }

    return v;
}

/*
Creates an identity matrix.

Inputs:
    -int nrows: number of rows,
    -int ncols: number of columns.

Output:
    -(nrows x ncols) identity matrix M.
*/
matrix eye(int nrows, int ncols) {
    matrix M(nrows, vec(ncols, 0));
    for (int i = 0; i < nrows; i++) {
        if (i < ncols) {
            M[i][i] = 1;
        }
    }
    return M;
}

/*
Creates a square identity matrix.

Inputs:
    -int n: matrix dimensions.

Output:
    -(n x n) identity matrix M.
*/
matrix eye(int n) {
    return eye(n, n);
}

/*
Calculate the tensor product (Kronecker product) of 2 matrices.

Inputs:
    -(nrowA x ncolA) matrix A,
    -(nrowB x ncolB) matrix B.

Output:
    -(nrowA*nrowB x ncolA*ncolB) tensor product of A and B.
*/
matrix tensor(const matrix &A, const matrix &B) {
    const unsigned int nrowA = A.size();
    const unsigned int ncolA = A[0].size();
    const unsigned int nrowB = B.size();
    const unsigned int ncolB = B[0].size();

    matrix T(nrowA*nrowB, vec(ncolA*ncolB, 0));

    for (unsigned int i1 = 0; i1 < nrowA; i1++) {
        for (unsigned int i2 = 0; i2 < nrowB; i2++) {
            for (unsigned int j1 = 0; j1 < ncolA; j1++) {
                for (unsigned int j2 = 0; j2 < ncolB; j2++) {
                    T[i1*nrowB+i2][j1*ncolB+j2] = A[i1][j1] * B[i2][j2];
                }
            }
        }
    }
    return T;
}

/*
Calculate the tensor product (Kronecker product) of 2 vectors.

Inputs:
    -vector u of length lenu,
    -vector v of length lenv.

Output:
    -tensor product of u and v of length lenu*lenv.
*/
vec tensor(const vec &u, const vec &v) {
    const unsigned int lenu = u.size();
    const unsigned int lenv = v.size();

    vec t(lenu*lenv, 0);
    for (unsigned int i = 0; i < lenu; i++) {
        for (unsigned int j = 0; j < lenv; j++) {
            t[i*lenv + j] = u[i] * v[j];
        }
    }
    return t;
}

/*
Prints matrix to standard output.

Inputs:
    -matrix A.
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

/*
Prints only the real components of each matrix cell to standard output.

Inputs:
    -matrix A.
*/
void printReal(const matrix &M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[i].size(); j++) {
            cout << real(M[i][j]) << ' ';
        }
        cout << '\n';
    }
    cout << endl;
}

/*
Prints vector to standard output.

Inputs:
    -vector A.
*/
void print(const vec &v) {
    print(matrix(1, v));
}

/*
Prints only the real components of each vector cell to standard output.

Inputs:
    -vector A.
*/
void printReal(const vec &v) {
    printReal(matrix(1, v));
}
