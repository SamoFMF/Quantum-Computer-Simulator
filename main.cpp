#include "matrix.h"
#include "qcs.cpp"
#include <iostream>
#include <math.h>

void interactiveBuilder() {
    // TODO - being developed
    // First input qubits as a string
    string inq;
    cin >> inq;
    qcs q = qcs(inq);

    // 1: Logic gate (e.g. H - Hadamard) || Doesn't apply to custom oracle
    // 2: Mode of input:
    //              -0: default, no arguments
    //              -1: There will be an optional number of arguments
    //              -2: Exactly 2 arguments (only available on 2-qubit gates)
    // 3: Number of args if mode 1, else appropriate amount of args
    string gate;
    int mode;
    int narg; // Number of arguments
    int ndim; // Dimension of custom oracle
    vector<unsigned int> idxs; // Indices
    unsigned int i, j; // Indices for mode 2
    matrix oracle; // Custom oracle
    complex<double> p;
    double real, imag;
}

int main() {
    qcs q = qcs("001");
    matrix Uf = {{1,0,0,0,0,0,0,0}, // Balanced function
                    {0,1,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0},
                    {0,0,1,0,0,0,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,1,0,0,0},
                    {0,0,0,0,0,0,1,0},
                    {0,0,0,0,0,0,0,1}};
    q.H({0,1,2});
    q.useOracle(0, Uf);
    q.H({0,1});

    q.measure({0,2});
    q.results();
}
