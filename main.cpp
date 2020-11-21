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

/*
Check online for quantum teleportation for an explanation.
*/
qcs quantumTeleportationCircuit(vec psi = {}) {
    if (psi.size() == 0) psi = {0.167060265149910+0.428660680349339i,0.703361116340482 + 0.541870860031018i};
    
    matrix M = {psi,{1,0},{1,0}};
    qcs q = qcs(M); // Initialize qcs with qubits |psi>, |0>, and |0>

    // Initial states
    q.results();

    // Entangle 2nd and 3rd qubit by using H on the 2nd one and then CNOT
    q.H(1);
    q.CX(1);

    // Apply CNOT to the 1st (control) and 2nd qubit and Hadamard to the 1st
    q.CX(0);
    q.H(0);

    // Measure 1st and 2nd qubit and save values to classical registers 0 and 1
    q.measureAndSave(0, 0);
    q.measureAndSave(1, 1);

    if (q.getBoolCR(1)) q.X(2);
    if (q.getBoolCR(0)) q.Z(2);

    // End states
    q.results();


    return q;
}

int main() {
    // qcs q = qcs("001");
    // matrix Uf = {{1,0,0,0,0,0,0,0}, // Balanced function
    //                 {0,1,0,0,0,0,0,0},
    //                 {0,0,0,1,0,0,0,0},
    //                 {0,0,1,0,0,0,0,0},
    //                 {0,0,0,0,0,1,0,0},
    //                 {0,0,0,0,1,0,0,0},
    //                 {0,0,0,0,0,0,1,0},
    //                 {0,0,0,0,0,0,0,1}};
    // q.H({0,1,2});
    // q.useOracle(0, Uf);
    // q.H({0,1});

    // q.measure({0,2});
    // q.results();
    // qcs q = qcs("001");
    // q.Y(0);
    // q.H(1);
    // q.CX(1);
    // q.CX(0);
    // q.H(0);
    // q.measureAndSave(0, 0);
    // q.measureAndSave(1, 1);
    // q.results();

    quantumTeleportationCircuit();
}
