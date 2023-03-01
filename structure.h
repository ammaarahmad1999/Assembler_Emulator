#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <bits/stdc++.h>
using namespace std;

class ListFileCode{
    public:
        string location;
        string label;
        string mnemonic;
        string operand;
        string byteCode;
        ListFileCode() : location("") , label(""), mnemonic(""), operand("") {}
        ListFileCode(string location, string label) : 
            location(location), label(label), mnemonic(""), operand("") {}
        ListFileCode(string location, string label, string mnemonic, string operand) : 
            location(location), label(label), mnemonic(mnemonic), operand(operand) {}
};


class Token{
	public:
		string token;
		string error;
		Token() : token(""), error("") {};
		Token(string token, string error) : token(token), error(error) {};
};

#endif