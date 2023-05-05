#define  _CRT_SECURE_NO_WARNINGS
#include "parser.h"
#include "memory.h"
namespace fs = std::filesystem;

//	AW: encapsulated your testing code here so i can test without your code running :swagger:
void parseTest()
{
	vector<string> instructions_string;
	vector<array<int, 4>> instructions;
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
	memory*		RISC_4GB = new memory();
	string		initFileTest = "./bin/RAWRS_init.txt";
	string		writeFileTest = "./bin/RAWRS_write.txt";
	fs::path*	initFilePath = new fs::path(initFileTest);
	fs::path*	writeFilePath = new fs::path(writeFileTest);
	int			buffer;

	RISC_4GB->set_initFile(initFilePath);
	RISC_4GB->set_writeFile(writeFilePath);
	RISC_4GB->init_memory(RISC_4GB->parse_init_file());
	RISC_4GB->write_memory_to_file('x');
	cin >> buffer;
	RISC_4GB->write_memory_to_file('b');
	cin >> buffer;
	RISC_4GB->write_memory_to_file('d');
}

int main()
{
	
	memoryTest();

	return		0;
}

