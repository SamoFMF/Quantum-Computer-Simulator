#include "matrix.h"
#include "qcs.cpp"
#include <iostream>

int main() {
    qcs q = qcs("0101");
    printReal(q.qubits);
    q.SWP({0,1,2});
    printReal(q.qubits);

    return 0;
}
