#ifndef MNEMONIC_H
#define MNEMONIC_H

#include <bits/stdc++.h>
using namespace std;
enum OperandType {BLANK, OFFSET, VALUE};

class Mnemonic{
    private:
        static unordered_map<string, string> mnemonicOpcodeMap;
        static unordered_map<string, OperandType>mnemonicOperandMap;
    public:
        static void readOpcodeFile();
        static void initializeMnemonicOperandMapping();
        static bool isValidMnemonic(string mnemonic);
        static string getOpcode(string mnemonic);
        static OperandType getOperandType(string mnemonic);
};

#endif