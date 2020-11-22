// Quantum Computer Simulator

#include "matrix.h"
#include "qcs.h"
#include "gates.h"
#include "utility.h"
#include "circuitView.h"

#include <math.h>
#include <iostream>
#include <ctime>
#include <random>
#include <string>


struct qcs {
    vec qubits; // Complex amplitudes of all qubits
    unsigned int n; // Number of qubits
    vector<bool> cr; // Classical register (register of booleans)

    // Create random generator and distribution
    mt19937_64 generator; // This will be initialized based on current time
    uniform_real_distribution<double> distribution; // This will be initialized to interval [0,1]
    string neki;
    circuitView view;


    qcs(string qs = "0") : generator((unsigned int) time(0)), distribution(0, 1) {
        matrix Q(qs.length(), vec(2, 0));
        for (unsigned int i = 0; i < qs.length(); i++) {
            if (qs.at(i) == '0') Q[i][0] = 1;
            else Q[i][1] = 1;
        }

        setupQubits(Q);
        view.begin(qs);
    }

    /*
    Construct qcs struct with desired cubits.

    Input:
        -(n x 2) matrix qubits, where each row represents a qubit.

    Output:
        -qcs struct.
    */
    qcs(matrix Q) : generator((unsigned int) time(0)), distribution(0, 1) {
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
        view.swap(idx);
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
        view.smallBox("X",{idx});
    }

    void X(vector<unsigned int> idxs) {
        useOracles(idxs, Xm);
        view.smallBox("X",idxs);
    }

    /*
    Use gate H (Hadamard) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use H.
    */
    void H(unsigned int idx = 0) {
        useOracle(idx, Hm);
        view.smallBox("H",{idx});
    }

    void H(vector<unsigned int> idxs) {
        useOracles(idxs, Hm);
        view.smallBox("H",idxs);
    }

    /*
    Use gate Y (Pauli-Y) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use H.
    */
    void Y(unsigned int idx = 0) {
        useOracle(idx, Ym);
        view.smallBox("Y",{idx});
    }

    void Y(vector<unsigned int> idxs) {
        useOracles(idxs, Ym);
        view.smallBox("Y",idxs);
    }

    /*
    Use gate Z (Pauli-Z) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use H.
    */
    void Z(unsigned int idx = 0) {
        useOracle(idx, Zm);
        view.smallBox("Z",{idx});
    }

    void Z(vector<unsigned int> idxs) {
        useOracles(idxs, Zm);
        view.smallBox("Z",idxs);
    }

    /*
    Use gate CX / CNOT (Controlled Not) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CX.
    */
    void CX(unsigned int idx = 0) {
        useOracle(idx, CXm);
        view.smallControlledBox("CNOT",idx);
    }

    void CX(vector<unsigned int> idxs) {
        useOracles(idxs, CXm);
        for (int i = 0; i < idxs.size(); i++)
        {
            view.smallControlledBox("CNOT",idxs[i]);
        }   
    }

    /*
    Use gate CX2 / CNOT2 (Controlled Not) on specified qubit where
        the second bit is the control bit.

    Input:
        -unsigned int idx: index of qubit on which to use CX2.
    */
    void CX2(unsigned int idx = 0) {
        useOracle(idx, CX2m);
        view.smallControlledBox("CNOT2",idx);
    }

    void CX2(vector<unsigned int> idxs) {
        useOracles(idxs, CX2m);
        for (int i = 0; i < idxs.size(); i++)
        {
            view.smallControlledBox("CNOT2",idxs[i]);
        }   
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
        view.smallBox("SQX",{idx});
    }

    void SQX(vector<unsigned int> idxs) {
        useOracles(idxs, SQXm);
        view.smallBox("SQX",idxs);
    }

    /*
    Use gate R (Phase Shift) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use R,
        -double phi: phase.
    */
    void R(unsigned int idx = 0, double phi = 0) {
        useOracle(idx, Rm(phi));
        view.smallBox("R",{idx});
    }

    void R(vector<unsigned int> idxs, double phi) {
        useOracles(idxs, Rm(phi));
        view.smallBox("R",idxs);
    }

    /*
    Use gate CR (Controlled Phase Shift) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CR,
        -double phi: phase.
    */
    void CR(unsigned int idx = 0, double phi = 0) {
        useOracle(idx, CRm(phi));
        view.smallControlledBox("CR",idx);
    }

    void CR(vector<unsigned int> idxs, double phi) {
        useOracles(idxs, CRm(phi));
        for (int i = 0; i < idxs.size(); i++)
        {
            view.smallControlledBox("CR",idxs[i]);
        }  
    }

    void CR(vector<unsigned int> idxs) {
        useOracles(idxs, CRm(0));
        for (int i = 0; i < idxs.size(); i++)
        {
            view.smallControlledBox("CR",idxs[i]);
        }  
    }

    void CR(unsigned int i, unsigned int j, double phi) {
        if (j-i == 1) CR(i, phi);
        else if (i < n-1) {
            SWP(j, i+1);
            CR(i, phi);
            SWP(j, i+1);
        } else if (j > 0) {
            SWP(i, j-1);
            CR(j-1, phi);
            SWP(i, j-1);
        } else {
            SWP(0);
            SWP(0, i);
            CR(0, phi);
            SWP(0, i);
            SWP(0);
        }
    }

    void CR(unsigned int i, unsigned int j) {
        CR(i, j, 0);
    }

    /*
    Use gate CCX (Toffoli / CCNOT // CCX) on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CCX.
    */
    void CCX(unsigned int idx = 0) {
        useOracle(idx, CCXm);
    }

    void CCX(vector<unsigned int> idxs) {
        useOracles(idxs, CCXm);
    }

    /*
    Use Quantum Fourier Transform (QFT) of desired size on specified qubit.

    Input:
        -unsigned int idx: index of qubit on which to use CCX,
        -unsigned int size: number of qubits on which QFT operates.
    */
    void QFT(unsigned int idx = 0, unsigned int size = 1) {
        useOracle(idx, QFTm(size));
    }

    /*
    Gathers the probabilities of all combinations of desired qubits given by indices.

    Input:
        -vector<unsigned int> idxs: a vector of indices of qubits to be taken into account.
            DEFAULT: If empty (or no) vector is given, all qubits are added.
    
    Output:
        -vector<double> probabilities: an ordered vector of probabilities of combinations
            of qubits (given by idxs) states.
    */
    vector<double> getProbabilities(vector<unsigned int> idxs) {
        vector<double> probabilities(1 << idxs.size(), 0);
        unsigned int x;
        unsigned int idx;
        for (unsigned int i = 0; i < qubits.size(); i++) {
            idx = 0;
            for (unsigned int j = 0; j < idxs.size(); j++) {
                // Create idx by finding idxs[j] value (0 or 1) in binary i
                // and then place it in the appropriate spot in idx,
                // which points to a value in probabilities
                idx += ((i >> (n - idxs[j] - 1)) & 1) << (idxs.size()-j-1);
            }
            probabilities[idx] += norm(qubits[i]);
        }
        return probabilities;
    }

    vector<double> getProbabilities() {
        vector<unsigned int> idxs(n, 0);
        for (unsigned int i = 1; i < n; i++) {
            idxs[i] = i;
        }
        return getProbabilities(idxs);
    }

    /*
    Measures desired qubits. This action is non-reversible, since measuring
        a qubit(s) is invasive, meaning the process transforms measured qubit(s)
        into either |0> or |1> state.

    Input:
        -vector<unsigned int> idxs: a vector of indices of qubits to be measured.
            DEFAULT: If empty (or no) vector is given, all qubits are measured.
    
    Output:
        -string measuredString: a string of 0s and 1s, where for any i in idxs,
            the value measuredString[i] shows that qubit[idxs[i]] is either
            |0> (if measuredString[i] is 0) or |1> (else).
    */
    string measure(vector<unsigned int> idxs) {
        // No args: add all qubits
        if (idxs.empty()) {
            idxs.resize(n, 0);
            for (unsigned int i = 1; i < n; i++) {
                idxs[i] = i;
            }
        }

        vector<double> probabilities = getProbabilities(idxs);

        // Generate a random value and pick appropriate index
        double val = distribution(generator);
        double p = 0;
        int randIdx = -1;
        for (unsigned int i = 0; i < probabilities.size() - 1; i++) {
            p += probabilities[i];
            if (val <= p) {
                randIdx = i;
                break;
            }
        }
        if (randIdx < 0) randIdx = probabilities.size()-1;

        // We now measured the value of desired qubits.
        // Now update the variable `qubits` variable to reflect
        // the invasion of reading qubits.
        // We do this by going through qubits and setting the probability
        // to 0 if that arrangement does not fit the measurements.
        // If it does fit, add the norm (probability) to common counter.
        int idx;
        double qnorm = 0;
        for (unsigned int i = 0; i < qubits.size(); i++) {
            // Extract the same form as `randIdx` from i.
            // Similar to `getProbabilities` method.
            idx = 0;
            for (unsigned int j = 0; j < idxs.size(); j++) {
                idx += ((i >> (n - idxs[j] - 1)) & 1) << (idxs.size()-j-1);
            }
            if (idx != randIdx) qubits[i] = 0;
            else qnorm += norm(qubits[i]);
        }

        // Divide all values by the square root of qnorm.
        // This updates the states of qubits based on the measurements.
        double sqnorm = sqrt(qnorm);
        for (unsigned int i = 0; i < qubits.size(); i++) {
            qubits[i] /= sqnorm;
        }

        string measuredString = intToString(randIdx, idxs.size());

        cout << "Measured qubits: " << measuredString << '\n';

        return measuredString;
    }

    string measure() {
        return measure({});
    }

    string measure(unsigned int idx) {
        vector<unsigned int> idxs = {idx};
        return measure(idxs);
    }

    bool measureAndSave(unsigned int idx = 0, int idxReg = -1) {
        vector<double> probabilities = getProbabilities({idx});
        double val = distribution(generator);
        int randIdx = val<=probabilities[0] ? 0 : 1;

        int idx1;
        double qnorm = 0;
        for (unsigned int i = 0; i < qubits.size(); i++) {
            // Extract the same form as `randIdx` from i.
            // Similar to `getProbabilities` method.
            if (((i >> (n-idx-1)) & 1) ^ randIdx) qubits[i] = 0;
            else qnorm += norm(qubits[i]);
        }

        double sqnorm = sqrt(qnorm);
        for (unsigned int i = 0; i < qubits.size(); i++) {
            qubits[i] /= sqnorm;
        }

        cout << "Qubit " << idx << " measured as: " << randIdx << '\n';

        // Save randIdx into classical register at index idxReg
        if (idxReg < 0 || idxReg >= cr.size()) {
            // Save measurement at the end of the register (new slot)
            cr.push_back(randIdx);
        } else {
            // Register already exists, save measurement into it
            cr[idxReg] = randIdx;
        }

        return randIdx;
    }

    /*
    Prints out possible qubit positions (with probability > 0)
        and their correspoding probabilities.

    Input:
        -double err (default 1e-16): the probability below which a position
            is considered to have probability of 0 and is not displayed.
    */
    void results(vector<unsigned int> idxs = {}, double err = 1e-16) {
        // No args: add all qubits
        if (idxs.empty()) {
            idxs.resize(n, 0);
            for (unsigned int i = 1; i < n; i++) {
                idxs[i] = i;
            }
        }
        vector<double> probabilities = getProbabilities(idxs);
        cout << "\nState : Probability\n";
        for (unsigned int i = 0; i < probabilities.size(); i++) {
            if (probabilities[i] < err) continue;
            cout << intToString(i, n) << " : " << probabilities[i] << '\n';
        }
        cout << '\n';
    }


    //////////////////////////////////////////////////////
    //////////////// CLASSICAL OPERATIONS ////////////////
    //////////////////////////////////////////////////////

    bool getBoolCR(unsigned int idx) {
        return (idx < 0 || idx >= cr.size()) ? cr.back() : cr[idx];
    }

    
};
