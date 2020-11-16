#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef vector<vector<double>> matrix;

matrix multiply(const matrix &A, const matrix &B);

matrix eye(const int nrows, const int ncols);

void print(const matrix &M);





#endif