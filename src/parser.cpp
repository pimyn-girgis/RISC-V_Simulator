#include "parser.h"
#include <cstdio>
#include <cstdlib>

// main parse Fx //
map<const char *, int>set_instruction_set()
{
	map<const char*, int> instruction_set =
	{
	{ ""      , 0  },
	{ "lui"   , 1  },
	{ "auipc" , 2  },
	{ "jal"   , 3  },
	{ "jalr"  , 4  },
	{ "beq"   , 5  },
	{ "bne"   , 6  },
	{ "blt"   , 7  },
	{ "bge"   , 8  },
	{ "bltu"  , 9  },
	{ "bgeu"  , 10 },
	{ "lb"    , 11 },
	{ "lh"    , 12 },
	{ "lw"    , 13 },
	{ "lbu"   , 14 },
	{ "lhu"   , 15 },
	{ "sb"    , 16 },
	{ "sh"    , 17 },
	{ "sw"    , 18 },
	{ "addi"  , 19 },
	{ "slti"  , 20 },
	{ "sltiu" , 21 },
	{ "xori"  , 22 },
	{ "ori"   , 23 },
	{ "andi"  , 24 },
	{ "slli"  , 25 },
	{ "srli"  , 26 },
	{ "srai"  , 27 },
	{ "add"   , 28 },
	{ "sub"   , 29 },
	{ "sll"   , 30 },
	{ "slt"   , 31 },
	{ "sltu"  , 32 },
	{ "xor"   , 33 },
	{ "srl"   , 34 },
	{ "sra"   , 35 },
	{ "or"    , 36 },
	{ "and"   , 37 },
	{ "fence" , 38 },
	{ "ecall" , 39 },
	{ "ebreak", 40 }
	};

	return instruction_set;
}

// Opens program.txt and returns a vector of strings containing the instructions
vector<string> Get_Instructions()
{
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
			case 39:
			case 40:
				TERMINATE(res, str, delim, nextInstruction, registers);
				break;
			default:
				printf("Invalid Instruction\n");
			}
		}
		count++;

	}

	//E: AW: Fx should return a value so I added this temp
	//return {};
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
