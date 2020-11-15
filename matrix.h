#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef vector<vector<double>> matrix;

void multiply(const matrix &A, const matrix &B, matrix &C);

void eye(int nrows, int ncols, matrix &M);

void print(const matrix &M);





#endif