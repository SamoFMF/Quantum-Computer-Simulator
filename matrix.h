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

matrix eye(const int n);

matrix tensor(const matrix &A, const matrix &B);

vec tensor(const vec &u, const vec &v);

void print(const matrix &M);

void printReal(const matrix &M);

void print(const vec &v);

void printReal(const vec &v);

void printRes(const vector<double> &v);



#endif