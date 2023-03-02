#include <bits/stdc++.h>
#include <fstream>
using namespace std;
struct opcode
{
	string mnemonic;
	string operand;
};
int main(int argc, char** argv)
{
	if(argc==2)
	{
		cout<<"-trace  show instruction trace"<<endl;
		cout<<"-read   show memory reads"<<endl;
		cout<<"-write  show memory writes"<<endl;
		cout<<"-before show memory dump before execution"<<endl;
		return 0;
	}
	string input = argv[2];
	string type = argv[1];
	opcode arr[21]={{"ldc","value"},{"adc","value"},{"ldl","offset"},
	{"stl","offset"},{"ldnl","offset"},{"stnl","offset"},{"add",""},
	{"sub",""},{"shl",""},{"shr",""},{"adj","value"},{"a2sp",""},{"sp2a",""},
	{"call","offset"},{"return","offset"},{"brz","offset"},{"brlz","offset"},
	{"br","offset"},{"halt",""},{"data","value"},{"set","value"}};
	ifstream fin(input, ios::binary);
	if(type=="-before")
	{
		int num, n=0;
		while(n<12)
		{
			fin.read((char*)&num, 4);
			printf("%08X\t%08X\n",n, num);
			n++;
		}
	}
	else if(type=="-trace" || type=="-after")
	{
		int num=0, cnt=0, stack_value;
		int A=0, B=0, PC=0, SP=4000;
		while(true)
		{
			cnt++;
			fin.read((char*)&num, 4);
			int rem=num&255;
			num=num-rem;
			num=num/256;
			if(type=="-trace")
			{
				printf("PC=%08X, SP=%08X, A=%08X, B=%08X ",PC,SP,A,B);
				cout<<arr[rem].mnemonic;
				printf(" %08X\n",num);
			}
			if(rem==18)
				break;
			else if(rem==0)
			{
				B=A;
				A=num;
			}
			else if(rem==1)
				A=A+num;
			else if(num==2)
			{
				B=A;
				A=stack_value;
			}
			else if(num==3)
			{
				stack_value=A;
				A=B;
			}
			else if(num==4)
			{

			}
			else if(num==5)
			{

			}
			else if(num==6)
				A+B+A;
			else if(num==7)
				A=B-A;
			else if(num==8)
				A=B<<A;
			else if(num==9)
				A=B>>A;
			else if(num==10)
				SP=SP+num;
			else if(num==11)
			{
				SP=A;
				A=B;
			}
			else if(num==12)
			{
				B=A;
				A=SP;
			}
			else if(num==13)
			{
				B=A;
				A=SP;
				SP+=num;
			}
			else if(num==14)
			{
				PC=A;
				A=B;
			}
			else if(num==15 && A==0)
				PC=PC+num;
			else if(num==16 && A<0)
				PC=PC+num;
			else if(num==17)
				PC=PC+num;
		}
		if(type=="-after")
		{
			int num, n=0;
			while(n<12)
			{	
				fin.read((char*)&num, 4);
				printf("%08X\t%08X\n",n, num);
				n++;
			}
		}
		printf("%d instructions executed",cnt);
	}
	else if(type=="-isa")
	{
		cout<<"Opcode\tMnemonic\tOperand\n";
		for(int i=0; i<=20; i++)
			cout<<i<<"\t"<<arr[i].mnemonic<<"\t\t"<<arr[i].operand<<endl;
	}
	else
	{
		printf("-trace  show instruction trace\n");
		printf("-read   show memory reads\n");
		printf("-write  show memory writes\n");
		printf("-before show memory dump before execution\n");
	}
}