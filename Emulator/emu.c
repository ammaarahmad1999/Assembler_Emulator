#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char* folderPath =  "../Assembly_Codes/";
int memory[0x100000];						//memory used for execution of program
struct opcode 								//instruvtion set architecture definiton
{
	char* mnemonic;
	char* operand;
};

struct opcode arr[21]={{"ldc","value"},{"adc","value"},{"ldl","offset"},
	{"stl","offset"},{"ldnl","offset"},{"stnl","offset"},{"add",""},
	{"sub",""},{"shl",""},{"shr",""},{"adj","value"},{"a2sp",""},{"sp2a",""},
	{"call","offset"},{"return",""},{"brz","offset"},{"brlz","offset"},
	{"br","offset"},{"halt",""},{"data","value"},{"set","value"}};

int readFile(char *fileName){
	char *inputFile;                        //object filename
    strcpy(inputFile, folderPath);
	strcat(inputFile, fileName);	
	FILE *fin=fopen(inputFile,"rb");		//reading machine code in binary mode
	int numberOfLines = 0;
	while(!feof(fin))						//read until end of file
	{
		fread(&memory[numberOfLines], sizeof(int), 1, fin);
		numberOfLines++;
	}
	numberOfLines--;
	return numberOfLines;
}

void memoryDump(int numberOfLines){
	int k=0;
	while(k<numberOfLines)
	{	
		printf("%08X\t%08X\n",k, memory[k]);
		k++;
	}
}

int execute(int numberOfLines, int trace){
	int num=0, cnt=0, rem=0, t=0, error = 0;
	int A=0, B=0, PC=0, SP=4096;
	while(1)									//executing line by line
	{
		if(PC>=numberOfLines)					// PC location exceeds memory read then break with segmentation fault
		{
			printf("Segmentation Fault\n");
			error = 1;
			break;
		}
		num=memory[PC];							//fetching machine code
		rem=num&255;							//fetching opcode
		num=num>>8;							    //operand
		if(trace==1)							// if trace = 1 print every line
		{
			if(rem>20)
				printf("PC=%08X, SP=%08X, A=%08X, B=%08X \n",PC,SP,A,B);
			else if(arr[rem].operand!="")
				printf("PC=%08X, SP=%08X, A=%08X, B=%08X %s %08X\n",PC,SP,A,B,arr[rem].mnemonic,num);
			else
				printf("PC=%08X, SP=%08X, A=%08X, B=%08X %s\n",PC,SP,A,B,arr[rem].mnemonic);
		}
		if(rem>18)
		{
			printf("ERROR: Unknown Opcode %d\n",rem);	//If opcode is greater than 18(decimal)
			error = 1;
			break;
		}
		if(rem==18)								// if halt stop execution
			break;
		else if(rem==0)							//ldc
		{
			B=A;
			A=num;
		}
		else if(rem==1)							//adc
			A=A+num;
		else if(rem==2)							//ldl
		{
			B=A;
			A=memory[SP+num];
		}
		else if(rem==3)							//stl
		{
			memory[SP+num]=A;
			A=B;
		}
		else if(rem==4)							//ldnl
			A=memory[A+num];		
		else if(rem==5)							//stnl
			memory[A+num]=B;
		else if(rem==6)							//add
			A=B+A;
		else if(rem==7)							//sub
			A=B-A;
		else if(rem==8)							//shl
			A=B<<A;
		else if(rem==9)							//shr
			A=B>>A;
		else if(rem==10)						//adj
			SP=SP+num;	
		else if(rem==11)						//a2sp
		{
			SP=A;
			A=B;
		}
		else if(rem==12)						//sp2a
		{
			B=A;
			A=SP;
		}
		else if(rem==13)						//call
		{
			B=A;
			A=PC;
			PC=PC+num;
		}
		else if(rem==14)						//return
		{
			PC=A;
			A=B;
		}
		else if(rem==15 && A==0)				//brz
			PC=PC+num;
		else if(rem==16 && A<0)					//brlz
			PC=PC+num;
		else if(rem==17)						//br
			PC=PC+num;
		cnt++;
		PC++;						//increment of PC after each execution
	}
	printf("%d instructions executed\n",cnt);		
	return error;
}

void showISA(){
	printf("Opcode\tMnemonic\tOperand\n");
	for(int i=0; i<=20; i++)
		printf("%d\t%s\t\t%s\n",i,arr[i].mnemonic,arr[i].operand);
}

int main(int argc, char** argv)
{
	if(argc==2)								// if no instruction is passed to emulator			
	{
		printf("-trace show instruction trace\n");
		printf("-isa show mnemonic and expected operands\n");
		printf("-after show memory dump after execution\n");
		printf("-before show memory dump before execution\n");
		return 0;
	}

    char *type = argv[1];					//instruction type
    char *fileName = argv[2];
	int numberOfLines = readFile(fileName);
	
	if(strcmp("-before",type)==0)				//before execution memory dump
		memoryDump(numberOfLines);
	else if(strcmp(type,"-trace")==0)			//execution of instructions
		execute(numberOfLines, 1);
	else if(strcmp(type,"-after")==0){
		if(execute(numberOfLines, 0) == 0)
			memoryDump(numberOfLines);			//memory dump after execution if no error
	}
	else if(strcmp(type,"-isa")==0)				//printing instruction set architecture
		showISA();
	else										//if unkonwn operarion is passed print valid operation
	{
		printf("-trace show instruction trace\n");
		printf("-isa show mnemonic and expected operands\n");
		printf("-after show memory dump after execution\n");
		printf("-before show memory dump before execution\n");
	}
}
