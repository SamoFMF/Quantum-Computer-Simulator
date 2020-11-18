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