#ifndef GATES_H
#define GATES_H

#include "matrix.h"
#include <math.h>
#include "utility.h"

// Quantum logic gates in matrix forms

// Matrix for negation - Also rotation around X-axis by pi radians
const matrix Xm = {{0, 1}, {1, 0}};

 // Matrix for CNOT (controlled not)
const matrix CXm = {{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,1,0}};

// Matrix for CNOT/CX (controlled not) where the 2nd qubit is the control qubit
const matrix CX2m = {{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0}};

// Hadamard matrix
const double hf = 1 / sqrt(2);// Hadamard matrix factor (1/sqrt(2))
const matrix Hm = {{hf,hf},{hf,-hf}};

// Pauli-Y: rotation around Y-axis by pi radians
const matrix Ym = {{0,-1i},{1i,0}};

// Pauli-Z: rotation around Z-axis by pi radians
const matrix Zm = {{1,0},{0,-1}};

// SQX: Square root of NOT gate
const matrix SQXm = {{1.0+1i,1.0-1i},{1.0-1i,1.0+1i}};

// Phase shift R
matrix Rm(double phi);

// Controlled phase shift CR
matrix CRm(double phi);

// SWAP Quantum Logic Gates
const matrix SWPm = {{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1}}; // Matrix to SWAP 1st and 2nd qubit
const matrix SWP2m = {{1,0,0,0,0,0,0,0}, // Matrix to SWAP 1st and 3rd qubit
                        {0,0,0,0,1,0,0,0},
                        {0,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,1,0},
                        {0,1,0,0,0,0,0,0},
                        {0,0,0,0,0,1,0,0},
                        {0,0,0,1,0,0,0,0},
                        {0,0,0,0,0,0,0,1}};
// Matrix to SWAP 1st and 5th (i+4) qubit
const matrix SWP4m = {{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}};



// Matrix to SWAP 1st and 9th (i+8) qubit
const vector<unsigned int> ones = {1,257,3,259,5,261,7,263,9,265,11,267,13,269,15,271,17,273,19,275,21,277,23,279,25,281,27,283,29,285,31,287,33,289,35,291,37,293,39,295,41,297,43,299,45,301,47,303,49,305,51,307,53,309,55,311,57,313,59,315,61,317,63,319,
                                    65,321,67,323,69,325,71,327,73,329,75,331,77,333,79,335,81,337,83,339,85,341,87,343,89,345,91,347,93,349,95,351,97,353,99,355,101,357,103,359,105,361,107,363,109,365,111,367,113,369,115,371,117,373,119,375,121,377,123,379,125,381,127,383,
                                    129,385,131,387,133,389,135,391,137,393,139,395,141,397,143,399,145,401,147,403,149,405,151,407,153,409,155,411,157,413,159,415,161,417,163,419,165,421,167,423,169,425,171,427,173,429,175,431,177,433,179,435,181,437,183,439,185,441,187,443,189,445,191,447,
                                    193,449,195,451,197,453,199,455,201,457,203,459,205,461,207,463,209,465,211,467,213,469,215,471,217,473,219,475,221,477,223,479,225,481,227,483,229,485,231,487,233,489,235,491,237,493,239,495,241,497,243,499,245,501,247,503,249,505,251,507,253,509,255,511,
                                    2,258,4,260,6,262,8,264,10,266,12,268,14,270,16,272,18,274,20,276,22,278,24,280,26,282,28,284,30,286,32,288,34,290,36,292,38,294,40,296,42,298,44,300,46,302,48,304,50,306,52,308,54,310,56,312,58,314,60,316,62,318,64,320,
                                    66,322,68,324,70,326,72,328,74,330,76,332,78,334,80,336,82,338,84,340,86,342,88,344,90,346,92,348,94,350,96,352,98,354,100,356,102,358,104,360,106,362,108,364,110,366,112,368,114,370,116,372,118,374,120,376,122,378,124,380,126,382,128,384,
                                    130,386,132,388,134,390,136,392,138,394,140,396,142,398,144,400,146,402,148,404,150,406,152,408,154,410,156,412,158,414,160,416,162,418,164,420,166,422,168,424,170,426,172,428,174,430,176,432,178,434,180,436,182,438,184,440,186,442,188,444,190,446,192,448,
                                    194,450,196,452,198,454,200,456,202,458,204,460,206,462,208,464,210,466,212,468,214,470,216,472,218,474,220,476,222,478,224,480,226,482,228,484,230,486,232,488,234,490,236,492,238,494,240,496,242,498,244,500,246,502,248,504,250,506,252,508,254,510,256,512};
matrix createSWP8m();
extern const matrix SWP8m;

// Toffoli: CCNOT/CCX/TOFF
const matrix CCXm = {{1,0,0,0,0,0,0,0},
                        {0,1,0,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,0,0},
                        {0,0,0,1,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0},
                        {0,0,0,0,0,1,0,0,0},
                        {0,0,0,0,0,0,1,0,0},
                        {0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,1,0}};


// Quantum Fourier Transform (QFT) and inverse
matrix QFTm(unsigned int n);
matrix QFTim(unsigned int n);




#endif