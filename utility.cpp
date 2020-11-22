#include "utility.h"

using namespace std;

string intToString(int x, int y) {
    string reverse = "";
    while (x > 0) {
        reverse += x%2==1 ? "1" : "0";
        x >>= 1;
    }
    string toReturn = "";
    for (unsigned int i = reverse.length(); i > 0; i--) {
        toReturn += reverse[i-1];
    }
    return y>toReturn.length() ? string(y-toReturn.length(), '0').append(toReturn) : toReturn;
}

string intToString(int x) {
    return intToString(x, 0);
}