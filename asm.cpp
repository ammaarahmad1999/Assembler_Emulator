#include <bits/stdc++.h>
#include "hexadecimal.cpp"
#include "assembler.cpp"
#include "mnemonic.cpp"
#include "number.cpp"
#include "util.cpp"


using namespace std;

int main(int argc, char **argv){
    string binary;
    
    //Initialize Hexadecimal Static Variables
    Hexadecimal::generateHexNumber();
    Hexadecimal::generateBinaryHexMapping(0, 0, binary);
    cout<<"Hexadecimal Initailized\n";

    //Initialize Mnemonic Static Variables
    Mnemonic::readOpcodeFile();
    Mnemonic::initializeMnemonicOperandMapping();
    cout<<"Mnemonic Initialized\n";
    
    string input = argv[1];
    //Call Assembler Constructor to assemble the file
    Assembler assembler(input);
}