#define  _CRT_SECURE_NO_WARNINGS
#include "parser.h"
#include "memory.h"
namespace fs = std::filesystem;

void memoryTest()
{
	memory*		RISC_4GB = new memory();
	std::string		initFileTest = "./bin/RAWRS_init.txt";
	std::string		writeFileTest = "./bin/RAWRS_write.txt";
	fs::path*	initFilePath = new fs::path(initFileTest);
	fs::path*	writeFilePath = new fs::path(writeFileTest);
	int			buffer;

	RISC_4GB->set_initFile(initFilePath);
	RISC_4GB->set_writeFile(writeFilePath);
	RISC_4GB->init_memory(RISC_4GB->parse_init_file());
	RISC_4GB->write_memory_to_file('x');
	std::cin >> buffer;
	RISC_4GB->write_memory_to_file('b');
	std::cin >> buffer;
	RISC_4GB->write_memory_to_file('d');
}

int main()
{
	
	memoryTest();

	return		0;
}

