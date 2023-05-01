#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

void LUI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void AUIPC(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void JAL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void JALR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BEQ(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BNE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BGE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BGEU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void LB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LBU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LHU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ADDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLTI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLTIU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void XORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ANDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRAI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ADD(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SUB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void XOR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRA(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void OR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void AND(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void TERMINATE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);

int main()
{
	vector<string> instructions_string;
	vector<int[4]> instructions;
	map<char*, int> labels;
	map<string, int>instruction_set;
	map<char*, int*> registers;
	instruction_set = Set_Instruction_Set();
	registers = set_registers();
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
map<char*, int*> set_registers()
{
	map<char*, int*> registers;
	vector<int*> registers_vec(32);
	for (int i = 0; i < registers_vec.size(); i++)
	{
		*registers_vec[i] = 0;
	}
	registers.insert({ "x1",registers_vec[0] });
	
	return registers;
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
map<char*, int> Get_Labels(vector<string>& instruction_string)
{
	map<char*, int> labels;
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
vector<int[4]> Translate_Instructions(vector<string>& instruction_string, map<string,int>& instruction_set, map<char*, int*> registers)
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
				LUI(res, str, delim, nextInstruction, registers);
				break;
			case 2:
				AUIPC(res, str, delim, nextInstruction, registers);
				break;
			case 3:
				JAL(res, str, delim, nextInstruction, registers);
				break;
			case 4:
				JALR(res, str, delim, nextInstruction, registers);
				break;
			case 5:
				BEQ(res, str, delim, nextInstruction, registers);
				break;
			case 6:
				BNE(res, str, delim, nextInstruction, registers);
				break;
			case 7:
				BLT(res, str, delim, nextInstruction, registers);
				break;
			case 8:
				BGE(res, str, delim, nextInstruction, registers);
				break;
			case 9:
				BLTU(res, str, delim, nextInstruction, registers);
				break;
			case 10:
				BGEU(res, str, delim, nextInstruction, registers);
				break;
			case 11:
				LB(res, str, delim, nextInstruction, registers);
				break;
			case 12:
				LH(res, str, delim, nextInstruction, registers);
				break;
			case 13:
				LW(res, str, delim, nextInstruction, registers);
				break;
			case 14:
				LBU(res, str, delim, nextInstruction, registers);
				break;
			case 15:
				LHU(res, str, delim, nextInstruction, registers);
				break;
			case 16:
				SB(res, str, delim, nextInstruction, registers);
				break;
			case 17:
				SH(res, str, delim, nextInstruction, registers);
				break;
			case 18:
				SW(res, str, delim, nextInstruction, registers);
				break;
			case 19:
				ADDI(res, str, delim, nextInstruction, registers);
				break;
			case 20:
				SLTI(res, str, delim, nextInstruction, registers);
				break;
			case 21:
				SLTIU(res, str, delim, nextInstruction, registers);
				break;
			case 22:
				XORI(res, str, delim, nextInstruction, registers);
				break;
			case 23:
				ORI(res, str, delim, nextInstruction, registers);
				break;
			case 24:
				ANDI(res, str, delim, nextInstruction, registers);
				break;
			case 25:
				SLLI(res, str, delim, nextInstruction, registers);
				break;
			case 26:
				SRLI(res, str, delim, nextInstruction, registers);
				break;
			case 27:
				SRAI(res, str, delim, nextInstruction, registers);
				break;
			case 28:
				ADD(res, str, delim, nextInstruction, registers);
				break;
			case 29:
				SUB(res, str, delim, nextInstruction, registers);
				break;
			case 30:
				SLL(res, str, delim, nextInstruction, registers);
				break;
			case 31:
				SLT(res, str, delim, nextInstruction, registers);
				break;
			case 32:
				SLTU(res, str, delim, nextInstruction, registers);
				break;
			case 33:
				XOR(res, str, delim, nextInstruction, registers);
				break;
			case 34:
				SRL(res, str, delim, nextInstruction, registers);
				break;
			case 35:
				SRA(res, str, delim, nextInstruction, registers);
				break;
			case 36:
				OR(res, str, delim, nextInstruction, registers);
				break;
			case 37:
				AND(res, str, delim, nextInstruction, registers);
				break;
			case 38:
				TERMINATE(res, str, delim, nextInstruction, registers);
				break;
			case 39:
				TERMINATE(res, str, delim, nextInstruction, registers);
				break;
			case 40:
				TERMINATE(res, str, delim, nextInstruction, registers);
				break;
			}
		}
		count++;
		
	}
	
}
void LUI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	int immediate = atoi(res);
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	int* reg = registers[res];
}
void AUIPC(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	int immediate = atoi(res);
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	int* reg = registers[res];
	
}
void JAL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*,int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	
	reg = registers[res];
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);
		while (res == "")
		{
			res = strtok_s(NULL, delim, &nextInstruction);
		}
		reg2 = registers[res];
		
	}
	else //label system
	{
		line = labels[res];	
	}
}
void JALR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}

	reg = registers[res];
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);
		while (res == "")
		{
			res = strtok_s(NULL, delim, &nextInstruction);
		}
		reg2 = registers[res];

	}
	else //label system
	{
		line = labels[res];
	}
}
void BEQ(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);

	}
	else //label system
	{
		line = labels[res];
	}
}
void BNE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);

	}
	else //label system
	{
		line = labels[res];
	}
}
void BLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);

	}
	else //label system
	{
		line = labels[res];
	}
}
void BGE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);

	}
	else //label system
	{
		line = labels[res];
	}
}
void BLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);

	}
	else //label system
	{
		line = labels[res];
	}
}
void BGEU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);

	}
	else //label system
	{
		line = labels[res];
	}
}
void LB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void LH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void LW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void LBU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void LHU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void SB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void SH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void SW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];
}
void ADDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	
}
void SLTI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void SLTIU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void XORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void ORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void ANDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);

	
}
void SLLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void SRLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void SRAI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	immediate = atoi(res);


}
void ADD(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void SUB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void SLL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void SLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void SLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void XOR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void SRL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void SRA(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void OR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void AND(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}
void TERMINATE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg2 = registers[res];

	while (res == "")
	{
		res = strtok_s(NULL, delim, &nextInstruction);
	}
	reg3 = registers[res];


}