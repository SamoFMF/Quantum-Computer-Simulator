#include "gates.h"

// Phase shift R
matrix Rm(double phi) {
    return {{1,0},{0, exp(1i * phi)}};
}

// Controlled phase shift CR
matrix CRm(double phi) {
    return {{1,0,0,0},
            {0,1,0,0},
            {0,0,1,0},
            {0,0,0,exp(1i * phi)}};
}

// Swap 1 and 9 (i+8)
matrix createSWP8m() {
    matrix M(512, vec(512, 0));
    for (unsigned int i = 0; i < 512; i++) {
        M[i][ones[i]-1] = 1;
    }

    return M;
}

const matrix SWP8m = createSWP8m();

// QFT
matrix QFTm(unsigned int n) {
    unsigned int N = 1 << n;

    const double sqrtNr = 1.0 / sqrt(N);
    matrix M(N, vec(N, sqrtNr));
    complex<double> val;
    const complex<double> fact = -2*E_PI/N * 1i;
    for (unsigned int i = 1; i < N; i++) {
        for (unsigned int j = i+1; j < N; j++) {
            val = exp(fact * (double)i * (double)j);
            val *= sqrtNr;
            M[i][j] = val;
            M[j][i] = val;
        }
        val = exp(fact * (double)i * (double)i);
        M[i][i] = val * sqrtNr;
    }
    return M;
}

// QFT inverse
matrix QFTim(unsigned int n) {
    unsigned int N = 1 << n;

    const double sqrtNr = 1.0 / sqrt(N);
    matrix M(N, vec(N, sqrtNr));
    complex<double> val;
    const complex<double> fact = 2*E_PI/N * 1i;
    for (unsigned int i = 1; i < N; i++) {
        for (unsigned int j = i+1; j < N; j++) {
            val = exp(fact * (double)i * (double)j);
            val *= sqrtNr;
            M[i][j] = val;
            M[j][i] = val;
        }
        val = exp(fact * (double)i * (double)i);
        M[i][i] = val * sqrtNr;
    }
    return M;
}