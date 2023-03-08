#ifndef HEXADECIMAL_H
#define HEXADECIMAL_H

#include <bits/stdc++.h>
using namespace std;

class Hexadecimal{
    private:
        static char hexCharacter[16];
        static unordered_map<string, char>binaryHex;
        static unordered_map<char, string>characterToBinary;
        static unordered_map<char, int>characterToInteger;
    
    public:
        static void generateHexNumber();
        static void generateBinaryHexMapping(int index, int number, string&binaryCode);
        static unsigned int ConvertHexToUnsignedInteger(string hex);
        static int ConvertHexToInteger(string hex);
        static bool isValidHex(string hex);
        static string AddPaddingToHex(string hex);
        static string ConvertBinaryToHex(string binary);
        static string ConvertOctalToHex(string octal);
        static string ConvertDecimalToHex(string decimal);
        static string ConvertDecimalToHex(int decimal);
};

#endif