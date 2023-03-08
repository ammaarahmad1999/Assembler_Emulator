#include <bits/stdc++.h>
#include "assembler.h"
#include "hexadecimal.h"
#include "mnemonic.h"
#include "number.h"
#include "util.h"

using namespace std;
// Change this constant in order  
string Assembler::folderPath =  "../Assembly_Codes/";

Assembler::Assembler(string input) {
	inputFilename = folderPath + input;
    size_t pos=input.find(".asm");			
    if(pos!=string::npos)
        input=input.substr(0,pos); 
    listFilename = folderPath + input + ".l";
    logFilename = folderPath + input + ".log";
    objectFilename = folderPath + input + ".o";
	assemble();
}

bool Assembler::readInputFile(){
    ifstream file;
    file.open(inputFilename,ios::in);
    if(!file){
        cout<<"ERROR: File Not found"<<endl;
        return false;
    }

    string line;			
	while(getline(file,line)){
        lines.push_back(line);
    }
    file.close();
    return true;			 
}

Token Assembler::extractLabel(string &line, int lineNumber){
	string label; stringstream error;
	size_t pos = line.find_first_of(':');
	if(pos == string::npos)
		return Token();

	label = line.substr(0, pos);
	line = Util::trim(line.substr(pos+1));
	if(!Util::isValidLabel(label)){
		error << "ERROR: Invalid label name on line " << lineNumber << "\n";
		return Token("", error.str());
	}
	
	if(Mnemonic::isValidMnemonic(label)){
		error << "ERROR: label name on line " << lineNumber << " is a reserved mnemonic\n";
		return Token("", error.str());
	}
	
	if(labels.count(label)){
		error << "ERROR: A duplicate label was found on line " <<lineNumber<<"\n";
		return Token("", error.str());
	}
	
	return Token(label, error.str());
}

Token Assembler::extractMnemonic(string&line, int lineNumber){
	string mnemonic; stringstream error;
	if(line == "")
		return Token(mnemonic, error.str());

	size_t pos = line.find_first_of(" \t");
	if(pos == string::npos){
		mnemonic = line;
		line = "";
	}
	else{
		mnemonic = line.substr(0, pos);
		line = Util::trim(line.substr(pos+1));
	}
	
	if(mnemonic.length()>0 && !Mnemonic::isValidMnemonic(mnemonic)){
		error << "ERROR: Illegal mnemonic on line "<<lineNumber<<"\n";	
		mnemonic = "";
	}

	return Token(mnemonic, error.str());
}

Token Assembler::extractOperand(string&line, int lineNumber){
	string operand; stringstream error;
	if(line == "")
		return Token(operand, error.str());

	size_t pos = line.find_first_of(" :,\t");
	if(pos == string::npos){
		operand = line;
		line = "";
	}
	else{
		operand = line.substr(0, pos);
		line = Util::trim(line.substr(pos+1));
	}
	
	if(line.length() > 0)
		error<<"ERROR: Extra information on line "<<lineNumber<<" at index " << pos<<"\n";

	return Token(operand, error.str());
}

Token Assembler::operandHexValue(string operand, int lineNumber){
	string hex; stringstream error;
	if(operand == ""){
		error << "ERROR: operand expected on line "<<lineNumber<<"\n";
		return Token(hex, error.str());
	}

	if(operand[0] < '0' && operand[0] > '9' && operand[0] != '-' && operand[0] != '+'){
		error<<"ERROR: A non numerical value: "<<operand<<" present, data or set instruction requires numeric value on line "<<lineNumber<<"\n";
		return Token(hex, error.str());
	}

	hex = Hexadecimal::AddPaddingToHex(operand);
	if(hex != "")
		return Token(hex, error.str());
	
	hex = Hexadecimal::ConvertDecimalToHex(operand);
	if(hex != "")
		return Token(hex, error.str());
	
	hex = Hexadecimal::ConvertOctalToHex(operand);
	if(hex != "")
		return Token(hex, error.str());
	
	error<<"ERROR: A non numerical value: "<<operand<<" present, data or set instruction requires numeric value on line "<<lineNumber<<"\n";
	return Token(hex, error.str());
}

void Assembler::generateListAndObjectFile(){
	ofstream listFile, objectFile;
	string print; unsigned int byteCode;
	listFile.open(listFilename, ios::out);
	objectFile.open(objectFilename, ios::binary);
	
	for (ListFileCode&line : tuples){
		if(line.location == ""){
			listFile<<"\n";
			continue;
		}
		
		if(line.mnemonic == ""){
			listFile<<line.location+"\t"+line.label+":\n";
			continue;
		}
		
		if(line.label == "")
			listFile<<line.location+" "+line.byteCode+"\t"+line.mnemonic+"\t"+line.operand+"\n";
		else
			listFile<<line.location+" "+line.byteCode+"\t"+line.label+":\t"
			+line.mnemonic+"\t"+line.operand+"\n";
		
		byteCode = Hexadecimal::ConvertHexToUnsignedInteger(line.byteCode);
		objectFile.write((char*)&byteCode, 4);
	}

	listFile.close();
	objectFile.close();
}

bool Assembler::firstPass(){
	ofstream logFile;
	logFile.open(logFilename, ios::out);
    bool error = false; 
	int lineNumber = 1, location = 0;
	Token label, mnemonic, operand, hex;
    size_t pos; string locationHex;
	for (string line : lines){
		if((pos = line.find_first_of(';')) != string::npos)
			line=line.substr(0,pos);
        line = Util::trim(line);
		transform(line.begin(), line.end(), line.begin(), ::tolower);

		if(line.length() == 0){
			tuples.push_back(ListFileCode());
			lineNumber++;
			continue;
		}

		locationHex = Hexadecimal::ConvertDecimalToHex(location);
		label = extractLabel(line, lineNumber);
		if(label.error != ""){
			logFile<<label.error;
			error = true;
		}
		else if(label.token != "")
			labels[label.token] = location;

		mnemonic = extractMnemonic(line, lineNumber);
		if(mnemonic.error != ""){
			logFile<<mnemonic.error;
			error = true;
		}

		if(mnemonic.token == ""){
			tuples.push_back(ListFileCode(locationHex, label.token));
			lineNumber++;
			continue;
		}

		operand = extractOperand(line, lineNumber);
		if(mnemonic.token != "set" && mnemonic.token != "data"){
			tuples.push_back(ListFileCode(locationHex, label.token, mnemonic.token, operand.token));
			lineNumber++;
			location++;
			continue;
		}

		hex = operandHexValue(operand.token, lineNumber);
		if(hex.error != ""){
			logFile<<hex.error;
			error = true;
		}
		else if(mnemonic.token == "set")
			labels[label.token] = Hexadecimal::ConvertHexToInteger(hex.token);
		
		tuples.push_back(ListFileCode(locationHex, label.token, mnemonic.token, operand.token));

		lineNumber++;
		location++;
    }
	
	logFile.close();
	return error;
}

bool Assembler::secondPass(){
	ofstream logFile, listFile;
	logFile.open(logFilename, ios::app);
	
	string zero(8,'0'), opcode, code = zero; Token hex;
	bool error = false; OperandType type;
	int lineNumber = 1, operand;
	for (ListFileCode&line : tuples){
		if(line.location == "" || line.mnemonic == ""){
			lineNumber++;
			continue;
		}

		opcode = Mnemonic::getOpcode(line.mnemonic);
		type = Mnemonic::getOperandType(line.mnemonic);

		if(type == BLANK) {
			if(line.operand != "") {
				logFile<<"ERROR: Unexpected operand present on line "<<lineNumber<<"\n";
				error = true;
			}
			code =  zero + opcode;
		}
		else {
			hex = Assembler::operandHexValue(line.operand, lineNumber); 
			if(hex.error == "")
				code = hex.token + opcode;
			else {
				auto iterator = labels.find(line.operand);
				if(iterator == labels.end()){
					logFile<<"ERROR: A non existent label was found on line "<<lineNumber<<"\n";
					error = true;
				}
				else {
					operand = iterator->second;
					if(type == OFFSET)
						operand = operand - Hexadecimal::ConvertHexToInteger(line.location) - 1;
					code = Hexadecimal::ConvertDecimalToHex(operand) + opcode;
					usedLabels.insert(line.operand);
				}	
			}
		}
		
		if(code[8] == '*')
			code = code.substr(0,8);
		else
			code = code.substr(2,8);
		line.byteCode = code;
		lineNumber++;
	}

	for (auto iterator : labels){
		if(usedLabels.count(iterator.first) == 0){
			cout<<"WARNING: unused label with name "<<iterator.first<<" at line "
			<<iterator.second<<"\n";
			logFile<<"WARNING: unused label with name "<<iterator.first<<" at line "
			<<iterator.second<<"\n";
		}
	}

	logFile.close();
	return error;
}

void Assembler::assemble(){
	if(!readInputFile()){
		cout<<"Error while reading file\n";
		return;
	}
	cout<<"File Read Succesfully\n";

	if(firstPass()){
		cout<<"Error during first pass. Check log file\n";
		return;
	}
	cout<<"First Pass Completed Successfully\n";

	if(secondPass()){
		cout<<"Error during second pass. Check log file\n";
		return;
	}
	cout<<"Second Pass Completed Successfully\n";
		
	generateListAndObjectFile();
}

