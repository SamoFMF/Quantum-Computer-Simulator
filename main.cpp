#include "matrix.h"
#include "qcs.cpp"
#include <iostream>
#include <math.h>

const unsigned int qbits_in = 3;

string shema_out[3*qbits_in];

void fillEmpty(){
    // dodaj ravno črto (dodaj nič) kjer ni elementa(funkcije).
    //int lengthMustBe = shema_out[a1[0]].length();
    int lengthMustBe = 0;
    for (int m = 0; m < sizeof(shema_out)/sizeof(shema_out[0]); m++)
    {
        if(shema_out[m].length() > lengthMustBe){
            lengthMustBe = shema_out[m].length();
        }
    }
    
    for (int i = 0; i < qbits_in; i++)
    {
        int line_length = lengthMustBe - shema_out[i*3].length();
        for (int k = 0; k < line_length; k++)
        {
            shema_out[i*3+0] += ' ';
            shema_out[i*3+1] += '_';
            shema_out[i*3+2] += ' ';       
        }
    }
}

int smallBox(string textInside, vector<unsigned int> boxLocations){
    for (int i = 0; i < boxLocations.size(); i++)
    {
        int x = boxLocations[i];
        shema_out[x*3+0] += "   _";
        for (int m = 0; m < textInside.length(); m++)
        {
            shema_out[x*3+0] += "_";
        }
        shema_out[x*3+0] += "_   ";
        
        shema_out[x*3+1] += "__| ";
        shema_out[x*3+1] += textInside;
        shema_out[x*3+1] += " |__";
        
        shema_out[x*3+2] += "  |_";
        for (int m = 0; m < textInside.length(); m++)
        {
            shema_out[x*3+2] += "_";
        }
        shema_out[x*3+2] += "_|  ";
    }
    fillEmpty();
    return 8 + textInside.length();
}

// 1st control, 2nd box
int smallControlledBox(string textInside, unsigned int boxLocation){
    int c_line = textInside.length()/2;

    shema_out[boxLocation*3+0] += "    ";
    shema_out[boxLocation*3+1] += "____";
    shema_out[boxLocation*3+2] += "    ";
    for (int k = 0; k < c_line; k++)
    {
        shema_out[boxLocation*3+0] += " ";
        shema_out[boxLocation*3+1] += "_";
        shema_out[boxLocation*3+2] += " ";
    }
    shema_out[boxLocation*3+0] += " ";
    shema_out[boxLocation*3+1] += ".";
    shema_out[boxLocation*3+2] += "|";
    for (int k = 0; k < c_line; k++)
    {
        shema_out[boxLocation*3+0] += " ";
        shema_out[boxLocation*3+1] += "_";
        shema_out[boxLocation*3+2] += " ";
    }
    shema_out[boxLocation*3+0] += "    ";
    shema_out[boxLocation*3+1] += "____";
    shema_out[boxLocation*3+2] += "    ";

    vector<unsigned int> boxLocations = {boxLocation + 1};

    for (int i = 0; i < boxLocations.size(); i++)
    {
        int x = boxLocations[i];
        shema_out[x*3+0] += "   _";
        for (int m = 0; m < textInside.length(); m++)
        {
            if(m == c_line){
                shema_out[x*3+0] += "|";
            }else{
                shema_out[x*3+0] += "_";
            }
        }
        shema_out[x*3+0] += "_   ";
        
        shema_out[x*3+1] += "__| ";
        shema_out[x*3+1] += textInside;
        shema_out[x*3+1] += " |__";
        
        shema_out[x*3+2] += "  |_";
        for (int m = 0; m < textInside.length(); m++)
        {
            shema_out[x*3+2] += "_";
        }
        shema_out[x*3+2] += "_|  ";
    }
    fillEmpty();
    return 8 + textInside.length();
}



int bigBox(string textInside, int boxSize, int boxLocation){
    //begin location 
    
    shema_out[boxLocation*3+0] += "   _";
    shema_out[boxLocation*3+1] += "__| ";
    shema_out[boxLocation*3+2] += "  | ";
    for (int m = 0; m < textInside.length(); m++)
    {
        shema_out[boxLocation*3+0] += "_";
        shema_out[boxLocation*3+2] += " ";
    }
    shema_out[boxLocation*3+1] += textInside;
    shema_out[boxLocation*3+0] += "_   ";
    shema_out[boxLocation*3+1] += " |__";
    shema_out[boxLocation*3+2] += " |  ";


    //end location
    int boxBottom = boxLocation + boxSize - 1;
    shema_out[boxBottom*3+0] += "  | ";
    shema_out[boxBottom*3+1] += "__| ";
    shema_out[boxBottom*3+2] += "  |_";
    for (int m = 0; m < textInside.length(); m++)
    {
        shema_out[boxBottom*3+0] += " ";
        shema_out[boxBottom*3+1] += " ";
        shema_out[boxBottom*3+2] += "_";
    }
    shema_out[boxBottom*3+0] += " |  ";
    shema_out[boxBottom*3+1] += " |__";
    shema_out[boxBottom*3+2] += "_|  ";


    //middle location []
    int v = boxLocation + 1;
    while(v < boxBottom){
        shema_out[v*3+0] += "  | ";
        shema_out[v*3+1] += "__| ";
        shema_out[v*3+2] += "  | ";
        for (int m = 0; m < textInside.length(); m++)
        {
            shema_out[v*3+0] += " ";
            shema_out[v*3+1] += " ";
            shema_out[v*3+2] += " ";
        }
        shema_out[v*3+0] += " |  ";
        shema_out[v*3+1] += " |__";
        shema_out[v*3+2] += " |  ";
        v++;
    }

    fillEmpty();

    return 8 + textInside.length();
}

void swap(int location){
    shema_out[location*3+0] += "       ";
    shema_out[location*3+1] += "__   __";
    shema_out[location*3+2] += "  \\ /  ";
    shema_out[location*3+3] += "   X   ";
    shema_out[location*3+4] += "__/ \\__";
    shema_out[location*3+5] += "       ";
    fillEmpty();
}

void interactiveBuilder() {
    // TODO - being developed
    // First input qubits as a string
    string inq;
    cin >> inq;
    qcs q = qcs(inq);

    // 1: Logic gate (e.g. H - Hadamard) || Doesn't apply to custom oracle
    // 2: Mode of input:
    //              -0: default, no arguments
    //              -1: There will be an optional number of arguments
    //              -2: Exactly 2 arguments (only available on 2-qubit gates)
    // 3: Number of args if mode 1, else appropriate amount of args
    string gate;
    int mode;
    int narg; // Number of arguments
    int ndim; // Dimension of custom oracle
    vector<unsigned int> idxs; // Indices
    unsigned int i, j; // Indices for mode 2
    matrix oracle; // Custom oracle
    complex<double> p;
    double real, imag;
}

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


    q.measure({0,2});
    q.results();
    

    string in_str = "001";

    for (int i = 0; i < in_str.length(); i++)
    {
        shema_out[i*3+0] = "     ";
        shema_out[i*3+1] = "|";
        shema_out[i*3+1] += in_str[i];
        shema_out[i*3+1] += ">__";
        shema_out[i*3+2] = "     ";
    }
    

    vector<unsigned int> a1 = {0,2};
    smallBox("nekiX", a1);
    
    vector<unsigned int> a2 = {2};
    smallBox("ETH", a2);

    vector<unsigned int> a3 = {0,1,2};
    smallBox("1233456", a3);

    bigBox("BTC",3,0);

    swap(0);

    swap(1);

    smallControlledBox("X", 0);
    smallControlledBox("CX", 1);
    smallControlledBox("CXX", 0);
    smallControlledBox("CXX1", 1);
    smallControlledBox("CXX34", 0);

    // koncni izpis
    for (int i = 0; i < 3*qbits_in; i++) {
        cout << shema_out[i]; 
        cout << '|';
        cout << '\n';
    }
    cout << '\n';
    cout << "_________________DONE_________________";
}
