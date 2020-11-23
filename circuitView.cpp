#include "matrix.h"
#include <iostream>
#include "circuitView.h"

circuitView::circuitView(){

}
void circuitView::begin(string in_qubits){
    if(off){ return;}
    qubits = in_qubits.length();
    circuit_out = new string[qubits*3];

    // build circuit begining
    for (int i = 0; i < in_qubits.length(); i++)
    {
        circuit_out[i*3+0] = "     ";
        circuit_out[i*3+1] = "|";
        circuit_out[i*3+1] += in_qubits[i];
        circuit_out[i*3+1] += ">__";
        circuit_out[i*3+2] = "     ";
    }
}

void circuitView::displayCircuit(){
    if(off){ return;}
    for (int i = 0; i < (3*qubits) + (3*n_reg); i++) {
        cout << circuit_out[i]; 
        cout << '+';
        cout << '\n';
    }
    cout << '\n';
}

void circuitView::fillEmpty(){
    // dodaj ravno črto (dodaj nič) kjer ni elementa(funkcije).
    //int lengthMustBe = shema_out[a1[0]].length();
    if(off){ return;}
    int lengthMustBe = 0;
    for (int m = 0; m < qubits*3; m++)
    {
        if(circuit_out[m].length() > lengthMustBe){
            lengthMustBe = circuit_out[m].length();
        }
    }
    
    for (int i = 0; i < qubits; i++)
    {
        int line_length = lengthMustBe - circuit_out[i*3].length();
        for (int k = 0; k < line_length; k++)
        {
            circuit_out[i*3+0] += ' ';
            circuit_out[i*3+1] += '_';
            circuit_out[i*3+2] += ' ';       
        }
    }

    for (int i = qubits; i < qubits+n_reg; i++)
    {
        int line_length = lengthMustBe - circuit_out[i*3].length();
        for (int k = 0; k < line_length; k++)
        {
            circuit_out[i*3+0] += ' ';
            circuit_out[i*3+1] += '=';
            circuit_out[i*3+2] += ' ';       
        }
    }
}

int circuitView::smallBox(string textInside, vector<unsigned int> boxLocations){
    if(off){ return 0;}
    for (int i = 0; i < boxLocations.size(); i++)
    {
        int x = boxLocations[i];
        circuit_out[x*3+0] += "   _";
        for (int m = 0; m < textInside.length(); m++)
        {
            circuit_out[x*3+0] += "_";
        }
        circuit_out[x*3+0] += "_   ";
        
        circuit_out[x*3+1] += "__| ";
        circuit_out[x*3+1] += textInside;
        circuit_out[x*3+1] += " |__";
        
        circuit_out[x*3+2] += "  |_";
        for (int m = 0; m < textInside.length(); m++)
        {
            circuit_out[x*3+2] += "_";
        }
        circuit_out[x*3+2] += "_|  ";
    }
    fillEmpty();

    return 8 + textInside.length();
}

// 1st control, 2nd box
int circuitView::smallControlledBox(string textInside, unsigned int boxLocation, bool secondControl){
    if(off){ return 0;}
    int c_line = textInside.length()/2;

    circuit_out[boxLocation*3+0] += "    ";
    circuit_out[boxLocation*3+1] += "____";
    circuit_out[boxLocation*3+2] += "    ";
    for (int k = 0; k < c_line; k++)
    {
        circuit_out[boxLocation*3+0] += " ";
        circuit_out[boxLocation*3+1] += "_";
        circuit_out[boxLocation*3+2] += " ";
    }
    circuit_out[boxLocation*3+0] += " ";
    circuit_out[boxLocation*3+1] += ".";
    circuit_out[boxLocation*3+2] += "|";
    for (int k = 0; k < c_line; k++)
    {
        circuit_out[boxLocation*3+0] += " ";
        circuit_out[boxLocation*3+1] += "_";
        circuit_out[boxLocation*3+2] += " ";
    }
    circuit_out[boxLocation*3+0] += "    ";
    circuit_out[boxLocation*3+1] += "____";
    circuit_out[boxLocation*3+2] += "    ";
    
    
    if(secondControl){
        boxLocation++;
        circuit_out[boxLocation*3+0] += "    ";
        circuit_out[boxLocation*3+1] += "____";
        circuit_out[boxLocation*3+2] += "    ";
        for (int k = 0; k < c_line; k++)
        {
            circuit_out[boxLocation*3+0] += " ";
            circuit_out[boxLocation*3+1] += "_";
            circuit_out[boxLocation*3+2] += " ";
        }
        circuit_out[boxLocation*3+0] += "|";
        circuit_out[boxLocation*3+1] += ".";
        circuit_out[boxLocation*3+2] += "|";
        for (int k = 0; k < c_line; k++)
        {
            circuit_out[boxLocation*3+0] += " ";
            circuit_out[boxLocation*3+1] += "_";
            circuit_out[boxLocation*3+2] += " ";
        }
        circuit_out[boxLocation*3+0] += "    ";
        circuit_out[boxLocation*3+1] += "____";
        circuit_out[boxLocation*3+2] += "    ";
    }

    boxLocation++;
    circuit_out[boxLocation*3+0] += "   _";
    for (int m = 0; m < textInside.length(); m++)
    {
        if(m == c_line){
            circuit_out[boxLocation*3+0] += "|";
        }else{
            circuit_out[boxLocation*3+0] += "_";
        }
    }
    circuit_out[boxLocation*3+0] += "_   ";
    
    circuit_out[boxLocation*3+1] += "__| ";
    circuit_out[boxLocation*3+1] += textInside;
    circuit_out[boxLocation*3+1] += " |__";
    
    circuit_out[boxLocation*3+2] += "  |_";
    for (int m = 0; m < textInside.length(); m++)
    {
        circuit_out[boxLocation*3+2] += "_";
    }
    circuit_out[boxLocation*3+2] += "_|  ";
    
    fillEmpty();
    
    return 8 + textInside.length();
}

// First box then control.
int circuitView::smallInvControlledBox(string textInside, unsigned int boxLocation){
    if(off){ return 0;}
    int x = boxLocation;
    circuit_out[x*3+0] += "   _";
    circuit_out[x*3+2] += "  |_";
    for (int m = 0; m < textInside.length(); m++)
    {
        circuit_out[x*3+0] += "_";
        circuit_out[x*3+2] += "_";
    }
    circuit_out[x*3+0] += "_   ";
    circuit_out[x*3+2] += "_|  ";

    circuit_out[x*3+1] += "__| ";
    circuit_out[x*3+1] += textInside;
    circuit_out[x*3+1] += " |__";


    int c_line = textInside.length()/2;
    x++;
    circuit_out[x*3+0] += "    ";
    circuit_out[x*3+1] += "____";
    for (int k = 0; k < c_line; k++)
    {
        circuit_out[x*3+0] += " ";
        circuit_out[x*3+1] += "_";
        circuit_out[x*3+2] += " ";
    }
    circuit_out[x*3+0] += "|";
    circuit_out[x*3+1] += "|";
    for (int k = 0; k < c_line; k++)
    {
        circuit_out[x*3+0] += " ";
        circuit_out[x*3+1] += "_";
        circuit_out[x*3+2] += " ";
    }
    circuit_out[x*3+0] += "    ";
    circuit_out[x*3+1] += "____";
    circuit_out[x*3+2] += "         ";

    fillEmpty();
    return 8 + textInside.length();
}


void circuitView::boxConnectedToReg(unsigned int boxLocation, unsigned int regLocation, string boxName){
    if(off){ return;}
    int old_n_reg = n_reg;
    if(n_reg < regLocation + 1){
        n_reg = regLocation + 1;

        // copy circuit_out array .. and add reg.
        string* temp = new string[qubits*3 + old_n_reg*3];
        for (int i = 0; i < (qubits + old_n_reg)*3; i++)
        {
            temp[i] = circuit_out[i];
        }
        
        circuit_out = new string[(qubits + n_reg)*3];
        for (int i = 0; i < (qubits + old_n_reg)*3; i++)
        {
            circuit_out[i] = temp[i];
        }
    }

    fillEmpty();

    circuit_out[boxLocation*3+0] += "   ___   ";
    //circuit_out[boxLocation*3+1] += "__| M |__"; // _/
    circuit_out[boxLocation*3+1] += "__|"+ boxName +"|__";
    circuit_out[boxLocation*3+2] += "  |___|  ";

    for (int i = boxLocation + 1; i < qubits; i++)
    {
        circuit_out[i*3+0] += "    |    ";
        circuit_out[i*3+1] += "____|____";
        circuit_out[i*3+2] += "    |    ";
    }
    for (int i = qubits; i < qubits + regLocation; i++)
    {
        circuit_out[i*3+0] += "    |    ";
        circuit_out[i*3+1] += "====|====";
        circuit_out[i*3+2] += "    |    ";
    }

    
    circuit_out[qubits*3+0+regLocation*3] += "    |    ";
    circuit_out[qubits*3+1+regLocation*3] += "====*====";
    circuit_out[qubits*3+2+regLocation*3] += "         ";

    fillEmpty();
}

void circuitView::swapN(unsigned int qubit1, unsigned int qubit2){
    circuit_out[qubit1*3+0] += "       ";
    circuit_out[qubit1*3+1] += "_______";
    circuit_out[qubit1*3+2] += "   |   ";
    for (int i = qubit1 + 1; i < qubit2; i++)
    {
        circuit_out[i*3+0] += "   |   ";
        circuit_out[i*3+1] += "___|___";
        circuit_out[i*3+2] += "   |   ";
    }
    circuit_out[qubit2*3+0] += "   |   ";
    circuit_out[qubit2*3+1] += "___|___";
    circuit_out[qubit2*3+2] += "       ";
    fillEmpty();
}


int circuitView::bigBox(string textInside, int boxSize, int boxLocation){
    //begin location 
    if(off){ return 0;}
    circuit_out[boxLocation*3+0] += "   _";
    circuit_out[boxLocation*3+1] += "__| ";
    circuit_out[boxLocation*3+2] += "  | ";
    for (int m = 0; m < textInside.length(); m++)
    {
        circuit_out[boxLocation*3+0] += "_";
        circuit_out[boxLocation*3+2] += " ";
    }
    circuit_out[boxLocation*3+1] += textInside;
    circuit_out[boxLocation*3+0] += "_   ";
    circuit_out[boxLocation*3+1] += " |__";
    circuit_out[boxLocation*3+2] += " |  ";


    //end location
    int boxBottom = boxLocation + boxSize - 1;
    circuit_out[boxBottom*3+0] += "  | ";
    circuit_out[boxBottom*3+1] += "__| ";
    circuit_out[boxBottom*3+2] += "  |_";
    for (int m = 0; m < textInside.length(); m++)
    {
        circuit_out[boxBottom*3+0] += " ";
        circuit_out[boxBottom*3+1] += " ";
        circuit_out[boxBottom*3+2] += "_";
    }
    circuit_out[boxBottom*3+0] += " |  ";
    circuit_out[boxBottom*3+1] += " |__";
    circuit_out[boxBottom*3+2] += "_|  ";


    //middle location []
    int v = boxLocation + 1;
    while(v < boxBottom){
        circuit_out[v*3+0] += "  | ";
        circuit_out[v*3+1] += "__| ";
        circuit_out[v*3+2] += "  | ";
        for (int m = 0; m < textInside.length(); m++)
        {
            circuit_out[v*3+0] += " ";
            circuit_out[v*3+1] += " ";
            circuit_out[v*3+2] += " ";
        }
        circuit_out[v*3+0] += " |  ";
        circuit_out[v*3+1] += " |__";
        circuit_out[v*3+2] += " |  ";
        v++;
    }

    fillEmpty();

    return 8 + textInside.length();
}
// swap length 1.
void circuitView::swap(int location){
    if(off){ return;}
    circuit_out[location*3+0] += "       ";
    circuit_out[location*3+1] += "__   __";
    circuit_out[location*3+2] += "  \\ /  ";
    circuit_out[location*3+3] += "   X   ";
    circuit_out[location*3+4] += "__/ \\__";
    circuit_out[location*3+5] += "       ";
    fillEmpty();
}
// swap length 1>  TODO
