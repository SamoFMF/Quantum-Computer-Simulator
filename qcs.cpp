// Quantum Computer Simulator

#include "matrix.h"
#include "qcs.h"
#include <math.h>

struct qcs {
    vec qubits; // Complex amplitudes of all qubits
    unsigned int n; // Number of qubits

    // Factor to multiply with at the end
    complex<double> factor = 1;

    // Hadamard matrix factor (1/sqrt(2))
    double Hf = 1 / sqrt(2);

    // Quantum logic gates in matrix forms
    const matrix Xm = {{0, 1}, {1, 0}}; // Matrix for negation
    const matrix CNOTm = {{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,1,0}}; // Matrix for CNOT (controlled not)
    const matrix SWPm = {{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,0}}; // Matrix for SWAP
    const matrix Hm = {{1,1},{1,-1}}; // Hadamard matrix without the 1/sqrt(2) factor

    qcs(string qs = "0") {
        matrix Q(qs.length(), vec(2, 0));
        for (unsigned int i = 0; i < qs.length(); i++) {
            if (qs.at(i) == '0') Q[i][0] = 1;
            else Q[i][1] = 1;
        }

        setupQubits(Q);
    }

    /*
    Construct qcs struct with desired cubits.

    Input:
        -(n x 2) matrix qubits, where each row represents a qubit.

    Output:
        -qcs struct.
    */
    qcs(matrix Q) {
        setupQubits(Q);
    }

    void setupQubits(matrix &M) {
        n = M.size();
        qubits = M[0];
        for (unsigned int i = 1; i < n; i++) {
            qubits = tensor(qubits, M[i]);
        }
    }

    /*
    Use gate SWP (swap) on specified qubit.

    Input:
        -unsigned int idx: swaps idx'th and (idx+1)'st qubits.
    */
    void SWP(unsigned int idx = 0) {
        matrix M;
        idx > 0 ? M = tensor(eye(1 << idx), SWPm) : M = SWPm;
        if (idx < n-2) M = tensor(M, eye(1 << n-2-idx));
        qubits = multiply(M, qubits);
    }

    /*
    Use gate SWP (swap) on specified qubits.

    Input:
        -vector<unsigned int> idxs: uses SWP on every index.
    */
    void SWP(vector<unsigned int> idxs) {
        for (unsigned int i = 0; i < idxs.size(); i++) {
            SWP(idxs[i]);
        }
    }

    /*
    Use gate X (negation) on specified qubits.

    Input:
        -vector<int> idxs: vector of indices of qubits on which to use X.
    */
    void X(vector<int> idxs) {
        // TODO
    }

    /*
    Use gate X (negation) on specified qubit.

    Input:
        -int idx: index of qubit on which to use X.
    */
    void X(int idx) {
        X({idx});
    }

    /*
    Use gate X (negation) on the first qubit.
    */
    void X() {
        X({0});
    }
    
};
