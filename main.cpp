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

    q.boolCR_X(2,1);
    q.boolCR_Z(2,0);

    //if (q.getBoolCR(1)) q.X(2);
    //if (q.getBoolCR(0)) q.Z(2);

    // End states
    q.resultsEnd();
}

void superdenseCoding(string msg = "00") {
    qcs q = qcs(string(msg.length(), '0'));

    // Create Bell state
    for (int i = 0; i < msg.length()-1; i++) {
        q.H(i);
        q.CX(i, msg.length()-1);
    }

    // // Alice encodes message
    for (unsigned int i = 0; i < msg.length()-1; i++) {
        if (msg.at(i) == '1') q.Z(i);
    }
    if (msg.at(msg.length()-1) == '1') q.X(0);

    // Bob decodes message
    for (int i = 0; i < msg.length()-1; i++) {
        q.CX(i, msg.length()-1);
        q.H(i);
    }
    
    q.measureEnd();
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
    q.Oracle(0, Uf);
    //q.useOracle(0, Uf);

    // Apply Hadamards gate to every qubit except the last one
    idxs.pop_back();
    q.H(idxs);

    // Measure every qubit except the last one
    q.measureEnd(idxs);
}
void displayCircuitTEST(){
    cout << "\n";
    circuitView view;
    view.begin("0010");
        
    vector<unsigned int> a1 = {0,2};
    view.smallBox("Z", a1);
    
    vector<unsigned int> a2 = {2};
    view.smallBox("X", a2);

    vector<unsigned int> a3 = {0,1,2};
    view.smallBox("1", a3);

    view.bigBox("X",3,0);

    view.swap(0);

    view.swap(1);

    view.smallControlledBox("X", 0);
    view.smallControlledBox("CX", 0);
    view.smallControlledBox("O", 0);
     
    view.boxConnectedToReg(1,0);
    view.boxConnectedToReg(2,0);
    view.boxConnectedToReg(0,4);
    view.boxConnectedToReg(1,2);

    view.smallInvControlledBox("Z", 1);
    view.smallInvControlledBox("Y", 0);

    view.swapN(0,2);
    view.swapN(0,1);
    view.swapN(1,2);
    view.swapN(0,3);

    view.smallControlledBox("Toffoli", 0,true);
    view.smallControlledBox("Toffoli", 1,true);
    view.displayCircuit();
}
int main() {
    // QTC
    cout << "QUANTUM TELEPORTATION\n";
    quantumTeleportationCircuit();

    cout << "\n----------------------\n\n" << "DEUTSCH-JOZSA ALGORITHM\n";
    algorithmDeutschJozsa();

    cout << "----------------------\n\n" << "SUPERDENSE CODING\n";
    cout << "Type the message to be sent: ";
    string msg;
    cin >> msg;
    superdenseCoding(msg);

    //displayCircuitTEST();
    
    return 0;
}
