#include <bits/stdc++.h>
#include "mnemonic.h"
using namespace std;

unordered_map<string, string> Mnemonic::mnemonicOpcodeMap;
unordered_map<string, OperandType>Mnemonic::mnemonicOperandMap;
void Mnemonic::readOpcodeFile(){
    ifstream file;
    file.open("../opcode.txt",ios::in);
    string mnemonic, opcode;			
	file>>mnemonic>>opcode;
	while(mnemonic!="end")					//loop for storing mnemonic-opcode key value pair in map
	{
		mnemonicOpcodeMap.insert({mnemonic,opcode});
		file>>mnemonic>>opcode;
	}
    file.close();			
}

void Mnemonic::initializeMnemonicOperandMapping(){
	string nonOperandMnemonic[] = {"add", "sub", "shr", "shl", "return", "a2sp", "sp2a", "halt"};
    for (string mnemonic : nonOperandMnemonic)
		mnemonicOperandMap[mnemonic] = BLANK;
	string offsetMnemonic[] = {"ldl", "stl", "ldnl", "stnl", "call", "brz", "brlz", "br"};
	for (string mnemonic : offsetMnemonic)
		mnemonicOperandMap[mnemonic] = OFFSET;
    string valueMnemonic[] = {"ldc", "adc", "adj", "set", "data"};
	for (string mnemonic : valueMnemonic)
		mnemonicOperandMap[mnemonic] = VALUE;
}

bool Mnemonic::isValidMnemonic(string mnemonic){
    return mnemonicOpcodeMap.count(mnemonic);
}

string Mnemonic::getOpcode(string mnemonic){
    return mnemonicOpcodeMap[mnemonic];
}

OperandType Mnemonic::getOperandType(string mnemonic){
	return mnemonicOperandMap[mnemonic];
}