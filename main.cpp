#include "matrix.h"
#include "qcs.cpp"
#include <iostream>
#include <math.h>

const unsigned int qbits_in = 3;

string shema_out[3*qbits_in];

template <size_t n> 
int findSize(int (&arr)[n]) 
{ 
    return n; 
} 

template <size_t n> 
int smallBox(string textInside, int (&boxLocations)[n]){
    for (int i = 0; i < n; i++)
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

    

    string in_str = "001";

    for (int i = 0; i < in_str.length(); i++)
    {
        shema_out[i*3+0] = "     ";
        shema_out[i*3+1] = "|";
        shema_out[i*3+1] += in_str[i];
        shema_out[i*3+1] += ">__";
        shema_out[i*3+2] = "     ";
    }
    

    int a1[] = {0,2};
    smallBox("nekiX", a1);
    
    int a2[] = {2};
    smallBox("ETH", a2);

    int a3[] = {0,1,2};
    smallBox("1233456", a3);

    bigBox("BTC",3,0);

    swap(0);

    swap(1);

    // koncni izpis
    for (int i = 0; i < 3*qbits_in; i++) {
        cout << shema_out[i]; 
        cout << '|';
        cout << '\n';
    }
    cout << '\n';
    cout << "_________________DONE_________________";

}
