
#include "memory.h"

std::pair<int, int>** memory::parse_init_file( )
{

	return {};
}

void memory::init_memory(std::pair<int, int>**)
{

}
													
void memory::print_memory(char printOption)
{

}
																									
void memory::write_memory_to_file(char printOption)
{

}

int memory::read_from_memory(int address)
{
	return (*block)[address];
}

void memory::write_to_memory( std::pair<int, int>* data )
{
	(*block)[data->first] = data->second;
}

memory::memory()
{
	block = {};
	sectionAddresses = {};
	size = {};
	fs::path* wF = new fs::path("\\RAWRS_write.txt");
	fs::path* iF = new fs::path("\\RAWRS_init.txt");
	writeFile = wF;				//by default the writeFile will be RAWRS_write
	initFile = iF;				//by default the initFile will be RAWRS_init

}

memory::memory(std::map<int, int>* b, std::map<std::string, int>* sA, long int s, fs::path* wF, fs::path* iF)
{
	block = b;
	sectionAddresses = sA;
	size = s;
	writeFile = wF;
	initFile = iF;
}

void memory::set_writeFile(fs::path* wF)
{
	writeFile = wF;
}

fs::path* memory::get_writeFile()
{
	return writeFile;
}

void memory::set_initFile(fs::path* iF)
{
	initFile = iF;
}

fs::path* memory::get_initFile()
{
	return initFile;
}
