// Quantum Computer Simulator

#include "matrix.h"
#include "qcs.h"
#include "gates.h"
#include <math.h>

struct qcs {
    vec qubits; // Complex amplitudes of all qubits
    unsigned int n; // Number of qubits

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
    Uses specified oracles on specified (by index) qubits, s.t.
    the first input of the oracle is the i-th qubit, where i is
    the corresponding index, and any other input (if an oracle
    takes it) is a subsequent qubit.

    WARNINGS:
        1. Indices must be ordered, else results are undefined.
        2. Difference between two subsequent indices must be
            atleast as big as the binary logarithm (or bit length)
            of the size (meaning 1 dimension) of the corresponding
            oracle. Meaning, you can't overlap oracles.

    Input:
        -vector<unsinged int> idxs: vector of indices,
        -vector<matrix> Oracle: vector of oracles in matrix forms
            which are used on the corresponding qubit.
    */
    void useOracles(vector<unsigned int> idxs, const vector<matrix> & Oracles) {
        // Both inputs need to be of the same size and have atleast 1 element
        if (idxs.size() == 0 || idxs.size() != Oracles.size()) return;

        matrix M = idxs[0]>0 ? tensor(eye(1 << idxs[0]), Oracles[0]) : Oracles[0];

        // Calculate lg(Oracles[size-1].size())
        unsigned int lb = idxs[0], v = Oracles[0].size();
        while (v > 1) {
            lb++;
            v >>= 1;
        }

        unsigned int idx;
        for (unsigned int i = 1; i < idxs.size(); i++) {
            idx = idxs[i];

            // Check if we need to add an identity matrix
            // between Oracles[i-1] and Oracles[i]
            if (idx > lb) M = tensor(M, eye(1 << idx-lb));

            // Add Oracles[i]
            M = tensor(M, Oracles[i]);

            // Calculate lg(Oracles[i-1].size())
            lb = idx, v = Oracles[i].size();
            while (v > 1) {
                lb++;
                v >>= 1;
            }
        }

        if (n > lb) M = tensor(M, eye(1 << n-lb));

        qubits = multiply(M, qubits);
    }

    void useOracles(vector<unsigned int> idxs, const matrix Oracle) {
        useOracles(idxs, vector<matrix>(idxs.size(), Oracle));
    }

    /*
    Uses the specified oracle s.t. the first input is the
    i'th qubit and any other input (if it exists) is a
    subsequent qubit.

    Input:
        -unsinged int i: index of the qubit that is the
            first input of the oracle,
        -matrix Oracle: oracle in matrix form which is used
            on i'th (and any subsequent indices if needed) qubit
    */
    void useOracle(unsigned int i, const matrix &Oracle) {
        useOracles({i}, {Oracle});
    }

    /*
    Use gate SWP (swap) on specified qubit.

    Input:
        -unsigned int idx: swaps idx'th and (idx+1)'st qubits.
    */
    void SWP(unsigned int idx = 0) {
        useOracle(idx, SWPm);
    }

    void SWP(vector<unsigned int> idxs) {
        useOracles(idxs, SWPm);
    }

    void SWP2(unsigned int idx) {
        useOracle(idx, SWP2m);
    }

    void SWP4(unsigned int idx) {
        useOracle(idx, SWP4m);
    }

    void SWP8(unsigned int idx) {
        useOracle(idx, SWP8m);
    }

    /*
    Swap ith and jth qubit.

    Input:
        -unsigned int i,
        -unsigned int j.
    */
    void SWP(unsigned int i, unsigned int j) {
        if (i == j) return; // Can't swap with itself

        unsigned int temp;
        if (i > j) {
            temp = i;
            i = j;
            j = temp;
        }

        // Use SWP8m until possible (j-i >= 8)
        vector<unsigned int> idx8;
        while (j-i >= 8) {
            idx8.push_back(i);
            SWP8(i);
            i += 8;
        }

        // Use SWP4m, until j-i>=4
        vector<unsigned int> idx4;
        while (j-i >= 4) {
            idx4.push_back(i);
            SWP4(i);
            i += 4;
        }

        // Use SWP2m if needed (j-i>=2)
        bool usedSWP2 = false;
        unsigned int idx2;
        if (j-i >= 2) {
            usedSWP2 = true;
            idx2 = i;
            SWP2(i);
            i += 2;
        }

        // Use final SWP if needed
        // Else remove the final swap
        if (i < j) SWP(i);
        else if (usedSWP2) usedSWP2 = false;
        else if (!idx4.empty()) idx4.pop_back();
        else idx8.pop_back();

        // Revert setup swaps
        if (usedSWP2) SWP2(idx2);
        while (!idx4.empty()) {
            SWP4(idx4.back());
            idx4.pop_back();
        }
        while (!idx8.empty()) {
            SWP8(idx8.back());
            idx8.pop_back();
        }
    }

    /*
    Use gate X (negation) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use X.
    */
    void X(unsigned int idx = 0) {
        useOracle(idx, Xm);
    }

    void X(vector<unsigned int> idxs) {
        useOracles(idxs, Xm);
    }

    /*
    Use gate H (Hadamard) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use H.
    */
    void H(unsigned int idx = 0) {
        useOracle(idx, Hm);
    }

    void H(vector<unsigned int> idxs) {
        useOracles(idxs, Hm);
    }

    /*
    Use gate Y (Pauli-Y) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use H.
    */
    void Y(unsigned int idx = 0) {
        useOracle(idx, Ym);
    }

    void Y(vector<unsigned int> idxs) {
        useOracles(idxs, Ym);
    }

    /*
    Use gate Z (Pauli-Z) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use H.
    */
    void Z(unsigned int idx = 0) {
        useOracle(idx, Zm);
    }

    void Z(vector<unsigned int> idxs) {
        useOracles(idxs, Zm);
    }

    /*
    Use gate CX / CNOT (Controlled Not) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CX.
    */
    void CX(unsigned int idx = 0) {
        useOracle(idx, CXm);
    }

    void CX(vector<unsigned int> idxs) {
        useOracles(idxs, CXm);
    }

    /*
    Use gate CX2 / CNOT2 (Controlled Not) on specified qubit where
        the second bit is the control bit.

    Input:
        -unsigned int idx: index of qubit on which to use CX2.
    */
    void CX2(unsigned int idx = 0) {
        useOracle(idx, CX2m);
    }

    void CX2(vector<unsigned int> idxs) {
        useOracles(idxs, CX2m);
    }

    void CX(unsigned int i, unsigned int j) {
        if (i == j) return;
        
        if (i < j) {
            if (j-i > 1) SWP(i, j-1);
            CX(j-1);
            if (j-i > 1) SWP(i, j-1);
        } else {
            if (i-j > 1) SWP(j, i-1);
            CX2(i-1);
            if (i-j > 1) SWP(j, i-1);
        }
    }

    /*
    Use gate SQX (Square Root Not) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use SQX.
    */
    void SQX(unsigned int idx = 0) {
        useOracle(idx, SQXm);
    }

    void SQX(vector<unsigned int> idxs) {
        useOracles(idxs, SQXm);
    }

    /*
    Use gate R (Phase Shift) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use R,
        -double phi: phase.
    */
    void R(unsigned int idx = 0, double phi = 0) {
        useOracle(idx, Rm(phi));
    }

    void R(vector<unsigned int> idxs, double phi) {
        useOracles(idxs, Rm(phi));
    }

    /*
    Use gate CR (Controlled Phase Shift) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CR,
        -double phi: phase.
    */
    void CR(unsigned int idx = 0, double phi = 0) {
        useOracle(idx, CRm(phi));
    }

    void CR(vector<unsigned int> idxs, double phi) {
        useOracles(idxs, CRm(phi));
    }

    /*
    Use gate CCX (Toffoli / CCNOT // CCX) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CCX,
        -double phi: phase.
    */
    void CCX(unsigned int idx = 0) {
        useOracle(idx, CCXm);
    }

    void CCX(vector<unsigned int> idxs) {
        useOracles(idxs, CCXm);
    }


    
};
