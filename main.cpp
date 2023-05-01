#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

void LUI(char* str, const char* delim, char* nextInstruction, map<string,vector<int>*> registers);
void AUIPC(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void JAL(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void JALR(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void BEQ(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void BNE(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void BLT(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void BGE(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void BLTU(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void BGEU(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void LB(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void LH(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void LW(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void LBU(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void LHU(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SB(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SH(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SW(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void ADDI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SLTI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SLTIU(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void XORI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void ORI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void ANDI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SLLI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SRLI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SRAI(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void ADD(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SUB(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SLL(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SLT(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SLTU(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void XOR(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SRL(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void SRA(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void OR(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void AND(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);
void TERMINATE(char* str, const char* delim, char* nextInstruction, map<string, vector<int>*> registers);

int main()
{
	vector<string> instructions_string;
	vector<int[4]> instructions;
	map<string, int> labels;
	map<string, int>instruction_set;
	instruction_set = Set_Instruction_Set();
	instructions_string = Get_Instructions();
	labels = Get_Labels(instructions_string);
	instructions = Translate_Instructions(instructions_string, instruction_set);


	return 0;
}

map<string, int>Set_Instruction_Set()
{
	map<string, int> instruction_set;
	instruction_set.insert({ "",0 });
	instruction_set.insert({ "lui",1 });
	instruction_set.insert({ "auipc",2 });
	instruction_set.insert({ "jal",3 });
	instruction_set.insert({ "jalr",4 });
	instruction_set.insert({ "beq",5 });
	instruction_set.insert({ "bne",6 });
	instruction_set.insert({ "blt",7 });
	instruction_set.insert({ "bge",8 });
	instruction_set.insert({ "bltu",9 });
	instruction_set.insert({ "bgeu",10 });
	instruction_set.insert({ "lb",11 });
	instruction_set.insert({ "lh",12 });
	instruction_set.insert({ "lw",13 });
	instruction_set.insert({ "lbu",14 });
	instruction_set.insert({ "lhu",15 });
	instruction_set.insert({ "sb",16 });
	instruction_set.insert({ "sh",17 });
	instruction_set.insert({ "sw",18 });
	instruction_set.insert({ "addi",19 });
	instruction_set.insert({ "slti",20 });
	instruction_set.insert({ "sltiu",21 });
	instruction_set.insert({ "xori",22 });
	instruction_set.insert({ "ori",23 });
	instruction_set.insert({ "andi",24 });
	instruction_set.insert({ "slli",25 });
	instruction_set.insert({ "srli",26 });
	instruction_set.insert({ "srai",27 });
	instruction_set.insert({ "add",28 });
	instruction_set.insert({ "sub",29 });
	instruction_set.insert({ "sll",30 });
	instruction_set.insert({ "slt",31 });
	instruction_set.insert({ "sltu",32 });
	instruction_set.insert({ "xor",33 });
	instruction_set.insert({ "srl",34 });
	instruction_set.insert({ "sra",35 });
	instruction_set.insert({ "or",36 });
	instruction_set.insert({ "and",37 });
	instruction_set.insert({ "fence",38 });
	instruction_set.insert({ "ecall",39 });
	instruction_set.insert({ "ebreak",40 });

	return instruction_set;
}
vector<string> Get_Instructions()
{
	ifstream file;
	vector <string> inst;
	string temp;
	file.open("program.txt");
	while (getline(file, temp))
	{
		inst.push_back(temp);
	}
	file.close();
	return inst;
}
map<string, int> Get_Labels(vector<string>& instruction_string)
{
	map<string, int> labels;
	istringstream stringStream;
	string temp;
	char* str;
	char* nextInstruction;
	char* res;
	for (int i = 0; i < instruction_string.size(); i++)
	{
		stringStream.str(instruction_string[i]);
		getline(stringStream, temp,':');
		if (temp.at(temp.size() - 1) == ':') //delete leading spaces and label
		{
			str = &temp[0];
			res = strtok_s(str, " ", &nextInstruction);
			while (res == "" && res!=NULL)
			{
				res = strtok_s(NULL, " ", &nextInstruction);
			}
			labels.insert({ res,i });
			instruction_string[i].erase(0,temp.length());
		}
		else //delete lines that are only spaces
		{
			bool only_space = true;
			for (int j = 0; j < temp.length() && only_space; j++)
			{
				if (temp[j] != ' ')
				{
					only_space = false;
				}
			}
			if (only_space)
			{
				instruction_string[i].erase(0, temp.length());
			}
		}
	}
	return labels;
}
vector<int[4]> Translate_Instructions(vector<string>& instruction_string, map<string,int>& instruction_set, map<string, vector<int>*> registers)
{
	char* str;
	char* nextInstruction;
	char* res;
	const char* delim = " ,()";
	int count;
	vector<int[4]> instructions;
	int arr[4];
	for (int i = 0; i < instruction_string.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[j] = 0;
		}
		count = 0;
		str = &instruction_string[i][0];
		str[instruction_string[i].length()] = '\0';
		res = strtok_s(str, delim, &nextInstruction);
		arr[0] = instruction_set[res];
		if (arr[0] != 0)
		{
			switch (arr[0])
			{
			case 1:
				LUI(str, delim, nextInstruction, registers);
				break;
			case 2:
				AUIPC(str, delim, nextInstruction, registers);
				break;
			case 3:
				JAL(str, delim, nextInstruction, registers);
				break;
			case 4:
				JALR(str, delim, nextInstruction, registers);
				break;
			case 5:
				BEQ(str, delim, nextInstruction, registers);
				break;
			case 6:
				BNE(str, delim, nextInstruction, registers);
				break;
			case 7:
				BLT(str, delim, nextInstruction, registers);
				break;
			case 8:
				BGE(str, delim, nextInstruction, registers);
				break;
			case 9:
				BLTU(str, delim, nextInstruction, registers);
				break;
			case 10:
				BGEU(str, delim, nextInstruction, registers);
				break;
			case 11:
				LB(str, delim, nextInstruction, registers);
				break;
			case 12:
				LH(str, delim, nextInstruction, registers);
				break;
			case 13:
				LW(str, delim, nextInstruction, registers);
				break;
			case 14:
				LBU(str, delim, nextInstruction, registers);
				break;
			case 15:
				LHU(str, delim, nextInstruction, registers);
				break;
			case 16:
				SB(str, delim, nextInstruction, registers);
				break;
			case 17:
				SH(str, delim, nextInstruction, registers);
				break;
			case 18:
				SW(str, delim, nextInstruction, registers);
				break;
			case 19:
				ADDI(str, delim, nextInstruction, registers);
				break;
			case 20:
				SLTI(str, delim, nextInstruction, registers);
				break;
			case 21:
				SLTIU(str, delim, nextInstruction, registers);
				break;
			case 22:
				XORI(str, delim, nextInstruction, registers);
				break;
			case 23:
				ORI(str, delim, nextInstruction, registers);
				break;
			case 24:
				ANDI(str, delim, nextInstruction, registers);
				break;
			case 25:
				SLLI(str, delim, nextInstruction, registers);
				break;
			case 26:
				SRLI(str, delim, nextInstruction, registers);
				break;
			case 27:
				SRAI(str, delim, nextInstruction, registers);
				break;
			case 28:
				ADD(str, delim, nextInstruction, registers);
				break;
			case 29:
				SUB(str, delim, nextInstruction, registers);
				break;
			case 30:
				SLL(str, delim, nextInstruction, registers);
				break;
			case 31:
				SLT(str, delim, nextInstruction, registers);
				break;
			case 32:
				SLTU(str, delim, nextInstruction, registers);
				break;
			case 33:
				XOR(str, delim, nextInstruction, registers);
				break;
			case 34:
				SRL(str, delim, nextInstruction, registers);
				break;
			case 35:
				SRA(str, delim, nextInstruction, registers);
				break;
			case 36:
				OR(str, delim, nextInstruction, registers);
				break;
			case 37:
				AND(str, delim, nextInstruction, registers);
				break;
			case 38:
				TERMINATE(str, delim, nextInstruction, registers);
				break;
			case 39:
				TERMINATE(str, delim, nextInstruction, registers);
				break;
			case 40:
				TERMINATE(str, delim, nextInstruction, registers);
				break;
			}
		}
		count++;
		
	}
	
}