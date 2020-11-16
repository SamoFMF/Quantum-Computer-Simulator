#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <complex>

using namespace std;

typedef vector<complex<double>> vec;
typedef vector<vec> matrix;

matrix multiply(const matrix &A, const matrix &B);

vec multiply(const matrix &A, const vec &u);

matrix eye(const int nrows, const int ncols);

matrix tensor(const matrix &A, const matrix &B);

vec tensor(const vec &u, const vec &v);

void print(const matrix &M);

void printReal(const matrix &M);

void printVec(const vec &v);

void printVecReal(const vec &v);



#endif