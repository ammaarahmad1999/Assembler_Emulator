#include <bits/stdc++.h>
#include "hexadecimal.h"
#include "number.h"
#include "util.h"
using namespace std;

char Hexadecimal::hexCharacter[16];
unordered_map<string, char> Hexadecimal::binaryHex;
unordered_map<char, string> Hexadecimal::characterToBinary;
unordered_map<char, int>Hexadecimal::characterToInteger;
string empty;

void Hexadecimal::generateHexNumber(){
    for (int i=0; i<10; i++)
        hexCharacter[i] = char(i+48);      // 48 is ASCII code for '0'
    for (int i=10; i<16; i++)
        hexCharacter[i] = char(i+55);      // 65 is ASCII code for 'A' so 65-10 = 55
}

void Hexadecimal::generateBinaryHexMapping(int index, int number, string&binaryCode){
    if(index == 4){
        binaryHex[binaryCode] = hexCharacter[number];
        characterToBinary[hexCharacter[number]] = binaryCode;
        return;
    }

    number <<= 1;
    // Adding 0 to binaryCode       
    binaryCode.push_back('0');
    generateBinaryHexMapping(index+1, number, binaryCode);
    binaryCode.pop_back();

    // Adding 1 to binaryCode
    binaryCode.push_back('1');
    generateBinaryHexMapping(index+1, number+1, binaryCode);
    binaryCode.pop_back();
}

bool Hexadecimal::isValidHex(string hex){
    if(hex.length() < 2 || hex.substr(0,2) != "0x")
        return false;
    
    for (int i=2; i<hex.length(); i++){
        if(characterToBinary.find(hex[i]) == characterToBinary.end())
            return false;
    }

    return true;
}

string Hexadecimal::AddPaddingToHex(string hex){
    if(!Number::isHex(hex))
        return empty;
    
    return Util::AddPadding(hex.substr(2), 8);
}

string Hexadecimal::ConvertBinaryToHex(string binary){
    string hex;
    binary = Util::AddPadding(binary, 32);
    int length = binary.length();
    for (int i=0; i<length; i+=4)
        hex.push_back(binaryHex[binary.substr(i,4)]);
    return hex;
}

string Hexadecimal::ConvertOctalToHex(string octal){
    if(!Number::isOctal(octal))
        return empty;

    string binary;
    for (char ch : octal)
        binary += characterToBinary[ch];
    
    return ConvertBinaryToHex(binary);
}

string Hexadecimal::ConvertDecimalToHex(string decimal){
    if(!Number::isDecimal(decimal))
        return empty;
    
    return ConvertDecimalToHex(stoi(decimal));
}

string Hexadecimal::ConvertDecimalToHex(int decimal){
    string hex(8, '0');
    for (int i=0; i<8; i++){
        hex[7-i] = hexCharacter[decimal&15];
        decimal >>= 4;
    }
    return hex;
}

int Hexadecimal::ConvertHexToInteger(string hex){
    int number = 0;
    for (char ch : hex){
        number <<= 4;
        number |= characterToInteger[ch];
    }

    return number;
}

unsigned int Hexadecimal::ConvertHexToUnsignedInteger(string hex){
    unsigned int number = 0;
    for (char ch : hex){
        number <<= 4;
        number |= characterToInteger[ch];
    }

    return number;
}