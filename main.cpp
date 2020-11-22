#include "matrix.h"
#include "qcs.cpp"
#include "circuitView.h"
#include <iostream>
#include <math.h>
#include <string.h>

// TODO - remove
#include <time.h>

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
void quantumTeleportationCircuit(vec psi = {}) {
    if (psi.empty()) psi = {0.167060265149910+0.428660680349339i,0.703361116340482 + 0.541870860031018i};
    
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
}

void superdenseCoding(string msg = "00") {
    qcs q = qcs("00");

    // Create Bell state
    q.H(0);
    q.CX(0);

    // // Alice encodes message
    if (msg.at(0) == '1') q.Z(0);
    if (msg.at(1) == '1') q.X(0);

    // Bob decodes message
    q.CX(0);
    q.H(0);

    q.measure({0,1});
}

void algorithmDeutschJozsa(matrix Uf = {}) {
    if (Uf.empty()) { // Use default oracle
        Uf = {{1,0,0,0,0,0,0,0}, // Balanced function
                {0,1,0,0,0,0,0,0},
                {0,0,0,1,0,0,0,0},
                {0,0,1,0,0,0,0,0},
                {0,0,0,0,0,1,0,0},
                {0,0,0,0,1,0,0,0},
                {0,0,0,0,0,0,1,0},
                {0,0,0,0,0,0,0,1}};
    }

    // Create qcs of appropriate size - based on size of Uf
    int n = 0; // Number of qubits
    int size = Uf.size();
    while (size > 1) {
        n++;
        size >>= 1;
    }
    qcs q = qcs(string(n-1, '0').append("1"));

    // Apply Hadamards gate on every qubit
    vector<unsigned int> idxs(n,0);
    for (unsigned int i = 1; i < n; i++) {
        idxs[i] = i;
    }
    q.H(idxs);

    // Use oracle
    q.useOracle(0, Uf);

    // Apply Hadamards gate to every qubit except the last one
    idxs.pop_back();
    q.H(idxs);

    // Measure every qubit except the last one
    q.measure(idxs);
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

    // QTC
    /*
    cout << "QUANTUM TELEPORTATION\n";
    quantumTeleportationCircuit();

    cout << "----------------------\n\n" << "SUPERDENSE CODING\n";
    superdenseCoding("01");

    cout << "----------------------\n\n" << "DEUTSCH-JOZSA ALGORITHM\n";
    algorithmDeutschJozsa();
*/
    // cout << "----------------------\n\n" << "QFT\n";
    // int n = 13;
    // clock_t start,end;
    // // matrix M = QFTm(n);
    // qcs q = qcs(string(n,'0'));
    // start = clock();
    // matrix M = QFTm(1);
    // q.useOracles({0,1,2,3,4,5,6,7,8,9,10,11}, Hm);
    // end = clock();
    // // print(q.qubits);
    // // q.results();

    // cout << ((float)(end-start))*1000/(CLOCKS_PER_SEC) << ' ';

    // qcs q1 = qcs(string(n,'0'));
    // start = clock();
    // matrix M1 = QFTm(n);
    // q1.useOracle(0, M1);
    // end = clock();

    // cout << ((float)(end-start))*1000/(CLOCKS_PER_SEC);
/*
    print(QFTm2);
    print(multiply(QFTm2, {1,0,0,0}));
*/

    circuitView view;
    view.begin("001");
        
    vector<unsigned int> a1 = {0,2};
    view.smallBox("nekiX", a1);
    
    vector<unsigned int> a2 = {2};
    view.smallBox("ETH", a2);

    vector<unsigned int> a3 = {0,1,2};
    view.smallBox("1233456", a3);

    view.bigBox("BTC",3,0);

    view.swap(0);

    view.swap(1);

    view.smallControlledBox("X", 0);
    view.smallControlledBox("CXX", 0);
    view.smallControlledBox("CXX34", 0);
     
    view.measureBox(1,0);
    view.measureBox(2,0);
    view.measureBox(0,4);
    view.measureBox(1,2);
    view.displayCircuit();

    return 0;
}
