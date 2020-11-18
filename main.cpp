#include "matrix.h"
#include "qcs.cpp"
#include <iostream>
#include <math.h>

int main() {
    qcs q = qcs("001");
    matrix Uf = {{1,0,0,0,0,0,0,0}, // Balanced function
                    {0,1,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0},
                    {0,0,1,0,0,0,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,1,0,0,0},
                    {0,0,0,0,0,0,1,0},
                    {0,0,0,0,0,0,0,1}};
    q.H({0,1,2});
    q.useOracle(0, Uf);
    q.H({0,1});
    print(q.qubits); // We get 11x, which means function is balanced (correct)
}
