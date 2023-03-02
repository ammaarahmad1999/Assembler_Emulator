#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <bits/stdc++.h>
#include "structure.h"
using namespace std;

class Assembler{
    private:
        // Input and Generated FileName 
        string inputFilename;
        string logFilename;
        string listFilename;
        string objectFilename;

        // Store lines from input file
        vector<string>lines;
        vector<ListFileCode>tuples;

        // Store Labels
        unordered_map<string,int>labels;
        unordered_set<string>usedLabels;

        // Hepler Functions to extract information from line
        Token extractLabel(string&line, int lineNumber);
        Token extractMnemonic(string&line, int lineNumber);
        Token extractOperand(string&line, int lineNumber);
        Token operandHexValue(string operand, int lineNumber);

        // Modular Functions
        void generateListAndObjectFile();
        bool readInputFile();
        bool firstPass();
        bool secondPass(); 

        // Constructor call this function to assemble the code
        void assemble();
    public:
        // Path to folder containing assembly line code
        static string folderPath;
        Assembler(string input);
};

#endif