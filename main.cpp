#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

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
vector<int[4]> Translate_Instructions(vector<string>& instruction_string, map<string,int>& instruction_set)
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

		}
		count++;
		
	}
	
}