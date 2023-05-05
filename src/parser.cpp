
#include "parser.h"

// main parse Fx //
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
	//this part deals with the x0...x31 way of calling registers
	char x = 'x';
	char* regs = new char[3];
	regs[0] = x;
	regs[3] = '\0';
	vector<int*> registers_vec(33);
	for (int i = 0; i < registers_vec.size(); i++)
	{
		*registers_vec[i] = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		regs[1] = i + '0';
		registers.insert({ regs,registers_vec[i] });
	}
	delete[] regs;
	char* regs = new char[4];
	regs[0] = x;
	regs[3] = '\0';
	regs[1] = '1';
	for (int i = 0; i < 10; i++)
	{
		regs[2] = i + '0';
		registers.insert({ regs,registers_vec[i+10] });
	}
	regs[1] = '2';
	for (int i = 0; i < 10; i++)
	{
		regs[2] = i + '0';
		registers.insert({ regs,registers_vec[i + 20] });
	}
	regs[1] = '3';
	for (int i = 0; i < 2; i++)
	{
		regs[2] = i + '0';
		registers.insert({ regs,registers_vec[i + 30] });
	}


	//this part deals with alternative naming
	//s10 and s11
	regs[0] = 's';
	regs[1] = '1';
	regs[2] = '0';
	registers.insert({ regs,registers_vec[26] });
	regs[2] = '1';
	registers.insert({ regs,registers_vec[27] });
	delete[] regs;
	char* regs = new char[3];
	//ra
	regs[0] = 'r';
	regs[1] = 'a';
	regs[2] = '\0';
	registers.insert({ regs,registers_vec[1] });
	//sp
	regs[0] = 's';
	regs[1] = 'p';

	registers.insert({ regs,registers_vec[2] });
	//gp
	regs[0] = 'g';
	regs[1] = 'p';

	registers.insert({ regs,registers_vec[3] });
	//tp
	regs[0] = 't';
	regs[1] = 'p';

	registers.insert({ regs,registers_vec[4] });
	//t0-t2
	for (int i = 0; i < 3; i++)
	{
		regs[1] = i + '0';
		registers.insert({ regs,registers_vec[5 + i] });
	}
	//t3-t6
	for (int i = 0; i < 4; i++)
	{
		regs[1] = i + 3 + '0';
		registers.insert({ regs,registers_vec[28 + i] });
	}
	//s0 and s1
	regs[0] = 's';
	for (int i = 0; i < 2; i++)
	{
		regs[1] = i + '0';
		registers.insert({ regs,registers_vec[8 + i] });
	}
	//s2 - s9
	for (int i = 0; i < 8; i++)
	{
		regs[1] = i + 2 + '0';
		registers.insert({ regs,registers_vec[18 + i] });
	}
	//a0-a7
	regs[0] = 'a';
	for (int i = 0; i < 8; i++)
	{
		regs[1] = i + '0';
		registers.insert({ regs,registers_vec[10 + i] });
	}
	//pc
	regs[0] = 'p';
	regs[1] = 'c';
	registers.insert({ regs,registers_vec[32] });

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
		getline(stringStream, temp, ':');
		if (temp.at(temp.size() - 1) == ':') //delete leading spaces and label
		{
			str = &temp[0];
			res = strtok(str, " ");
			while (res && !*res)
			{
				res = strtok(NULL, " ");
			}
			labels.insert({ res,i });
			instruction_string[i].erase(0, temp.length());
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
void Translate_Instructions(vector<string>& instruction_string, map<string, int>& instruction_set, map<char*, int*> registers)
{
	char* str;
	char* nextInstruction = {};
	char* res;
	const char* delim = " ,()";
	int count;
	vector<array<int, 4>> instructions;
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
		res = strtok(str, delim);
		arr[0] = instruction_set[res];
		if (arr[0] != 0)
		{
			switch (arr[0])
			{
			case 1:
				//AW:  unintialized variable nextInstruction
				//E: LUI(res, str, delim, nextInstruction, registers);
				break;
			case 2:
				//E: AUIPC(res, str, delim, nextInstruction, registers);
				break;
			case 3:
				//E: JAL(res, str, delim, nextInstruction, registers);
				break;
			case 4:
				//E: JALR(res, str, delim, nextInstruction, registers);
				break;
			case 5:
				//E: BEQ(res, str, delim, nextInstruction, registers);
				break;
			case 6:
				//E: BNE(res, str, delim, nextInstruction, registers);
				break;
			case 7:
				//E: BLT(res, str, delim, nextInstruction, registers);
				break;
			case 8:
				//E: BGE(res, str, delim, nextInstruction, registers);
				break;
			case 9:
				//E: BLTU(res, str, delim, nextInstruction, registers);
				break;
			case 10:
				//E: BGEU(res, str, delim, nextInstruction, registers);
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

	//E: AW: Fx should return a value so I added this temp
	return {};
}

//	instruction parsers	//

void LUI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	int immediate = atoi(res);
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	int* reg = registers[res];
}
void AUIPC(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	int immediate = atoi(res);
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	int* reg = registers[res];

}
void JAL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels)
{
	int* reg;
	int* reg2;
	int immediate;
	int line;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}

	reg = registers[res];
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);
		while (res && !*res)
		{
			res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}

	reg = registers[res];
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	if (res[0] < '0' || res[0]>'9') //offset address system
	{
		immediate = atoi(res);
		while (res && !*res)
		{
			res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
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
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void LH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void LW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void LBU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void LHU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void SB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void SH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void SW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];
}
void ADDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void SLTI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void SLTIU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void XORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void ORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void ANDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void SLLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void SRLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void SRAI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	immediate = atoi(res);


}
void ADD(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void SUB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void SLL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void SLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void SLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void XOR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void SRL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void SRA(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void OR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void AND(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
void TERMINATE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers)
{
	int* reg;
	int* reg2;
	int* reg3;
	int immediate;
	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg2 = registers[res];

	while (res && !*res)
	{
		res = strtok(NULL, delim);
	}
	reg3 = registers[res];


}
