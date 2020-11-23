#ifndef CIRCUITVIEW_H
#define CIRCUITVIEW_H

class circuitView{
    private:
        unsigned int qubits = 0;
        string* circuit_out;
        unsigned int n_reg = 0;
        bool off = false;
    public:
        circuitView();
        void begin(string in_qubits);
        void displayCircuit();
        void fillEmpty();
        int smallBox(string textInside, vector<unsigned int> boxLocations);
        int smallControlledBox(string textInside, unsigned int boxLocation);
        int smallInvControlledBox(string textInside, unsigned int boxLocation);
        void measureAndSave(unsigned int boxLocation, unsigned int regLocation);
        int bigBox(string textInside, int boxSize, int boxLocation);
        void swap(int location);
};

#endif