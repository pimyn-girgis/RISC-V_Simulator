
#include "parser.h"


//	AW: encapsulated your testing code here so i can test without your code running :swagger:
void parseTest()
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
	//E: instructions = Translate_Instructions(instructions_string, instruction_set);
}

void memoryTest()
{
	
}

int main()
{
	
	memoryTest();

	return 0;
}

