// Quantum Computer Simulator

#include "matrix.h"
#include "helper.h"

struct qcs {
    matrix qubits; // Initial qubits
    vec bell; // Bell state

    const matrix Xm = {{0, 1}, {1, 0}}; // Matrix for negation
    const matrix CNOTm = {{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,1,0}}; // Matrix for CNOT (controlled not)

    /*
    Construct qcs struct with desired cubits.

    Input:
        -(n x 2) matrix qubits, where each row represents a qubit.

    Output:
        -qcs struct.
    */
    qcs(matrix qubits) {
        this->qubits = qubits;
        bell.resize(1 << qubits.size()); // Correct if qubits.size() is atleast 1

        // TODO - use tenzor product on qubits to fill out bell
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
