#include "utility.h"

using namespace std;

string intToString(int x) {
    string reverse = "";
    while (x > 0) {
        reverse += x%2==1 ? "1" : "0";
        x >>= 1;
    }
    string toReturn = "";
    for (unsigned int i = reverse.length(); i > 0; i--) {
        toReturn += reverse[i-1];
    }
    return toReturn;
}