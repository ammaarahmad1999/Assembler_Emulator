#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char* folderPath =  "../Assembly_Codes/";
struct opcode 								//instruvtion set architecture definiton
{
	char* mnemonic;
	char* operand;
};
int main(int argc, char** argv)
{
	int memory[0x100000];					//memory used for execution of program
	if(argc==2)								// if no instruction is passed to emulator			
	{
		printf("-trace show instruction trace\n");
		printf("-isa show mnemonic and expected operands\n");
		printf("-after show memory dump after execution\n");
		printf("-before show memory dump before execution\n");
		return 0;
	}
    
    struct opcode arr[21]={{"ldc","value"},{"adc","value"},{"ldl","offset"},
	{"stl","offset"},{"ldnl","offset"},{"stnl","offset"},{"add",""},
	{"sub",""},{"shl",""},{"shr",""},{"adj","value"},{"a2sp",""},{"sp2a",""},
	{"call","offset"},{"return",""},{"brz","offset"},{"brlz","offset"},
	{"br","offset"},{"halt",""},{"data","value"},{"set","value"}};

    char *type = argv[1];					//instruction type
    char *inputFile;                        //object filename
    strcpy(inputFile, folderPath);
	strcat(inputFile, argv[2]);	
	
	FILE *fin=fopen(inputFile,"rb");		//reading machine code in binary mode
	int n=0, error=0;
	while(!feof(fin))						//read until end of file
	{
		fread(&memory[n], sizeof(int), 1, fin);
		n++;
	}
	n--;
	if(strcmp("-before",type)==0)			//before execution memory dumP
	{
		int k=0;
		while(k<n)
		{	
			printf("%08X\t%08X\n",k, memory[k]);
			k++;
		}
	}
	else if(strcmp(type,"-trace")==0 || strcmp(type,"-after")==0)			//execution of instructions
	{
		int num=0, cnt=0, rem=0, t=0;
		int A=0, B=0, PC=0, SP=4096;
		while(1)									//executing line by line
		{
			if(PC>=n)								// PC location exceeds memory read then break with segmentation fault
			{
				printf("Segmentation Fault\n");
				break;
			}
			num=memory[PC];							//fetching machine code
			rem=num&255;							//fetching opcode
			num=num>>8;							    //operand
			if(strcmp(type,"-trace")==0)			// if tracing print every line
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
				error=1;
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
		if(error==0 && strcmp(type,"-after")==0)			//memory dump after execution
		{
			int k=0;
			while(k<n)
			{	
				printf("%08X\t%08X\n",k, memory[k]);
				k++;
			}
		}
	}
	else if(strcmp(type,"-isa")==0)				//printing instruction set architecture
	{
		printf("Opcode\tMnemonic\tOperand\n");
		for(int i=0; i<=20; i++)
			printf("%d\t%s\t\t%s\n",i,arr[i].mnemonic,arr[i].operand);
	}
	else										//if unkonwn operarion is passed print valid operation
	{
		printf("-trace show instruction trace\n");
		printf("-isa show mnemonic and expected operands\n");
		printf("-after show memory dump after execution\n");
		printf("-before show memory dump before execution\n");
	}
}
