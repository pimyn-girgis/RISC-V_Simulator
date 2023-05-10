#define  _CRT_SECURE_NO_WARNINGS
#include "memory.h"

//AW: i could parse and initialise immediately but i chose to do it this way to so i have the parsed data accessible for the GUI
//AW: might put the return vector as member in the class w 5alas 

addressDataPairs* memory::parse_init_file()
{
	std::ifstream		initFileStream;
	std::string			line;
	int					data;
	size_t					address;
	addressDataPair*	tempPair = new addressDataPair();
	addressDataPairs*	parsedPairs = new addressDataPairs();

	initFileStream.open(*_initFile);

	if (initFileStream.is_open())
	{ 
		while (getline(initFileStream, line))
		{
			//AW: ignore comments and go to next line
			if (line[0] == '#' || line == "") 
			{
				continue;
			}

			//AW: see which format its written in
			switch (line[1])
			{
			case('x'):

				//AW: hardcoded here need to switch it up later or put a validation to check address/data format
				address = stoi(line.substr(2, 2+8), nullptr, 16);	//AW: conversions from string <str><pos><base conversion>
				data = stoi(line.substr(15, 15+8), nullptr, 16);

				break;

			case('b'):

				address = stoi(line.substr(2, 2+8*4), nullptr, 2);
				data = stoi(line.substr(38, 38+8*4), nullptr, 2);

				break;

			case('d'):

				address = stoi(line.substr(2, 2+10));
				data = stoi(line.substr(17, 17+10));

				break;

			default: //default is hex

				address = stoi(line.substr(2, 2 + 8), nullptr, 16);	
				data = stoi(line.substr(15, 15 + 8), nullptr, 16);
				
			}

			tempPair = new std::pair(address, data);
			parsedPairs->push_back(tempPair);

		}
	}
	else
	{
		printf("unable to open file");
	}

	return parsedPairs;
}

void memory::init_memory(addressDataPairs* parsedPairs)
{
	for (addressDataPair* j : *parsedPairs)
	{
		_block->insert(*j);
	}
}
													
void memory::print_memory(char printOption)
{
	for (addressDataPair j : *_block)
	{
		switch (printOption)
		{
		case ('x'):
			printf("0x%08x, 0x%08x\n", j.first, j.second);
			break;
		case ('b'):
			std::cout << "0b" << std::bitset<32>(j.first) << ", 0b" << std::bitset<32>(j.second) << '\n';
			break;
		case ('d'):
			printf("0d%010d, 0d%010d\n", j.first, j.second);
			break;
		default:
			printf("0x%08x, 0x%08x\n", j.first, j.second);
		}
	}
}
																									
void memory::write_memory_to_file(char printOption)
{
	std::ofstream		writeFileStream;
	char				line[72];			//AW: biggest is binary representation, 72 chars, could have done it differently tbh but this works ig
	std::string			lineStr;			//AW: for binary

	writeFileStream.open(*_writeFile);

	if (writeFileStream.is_open())
	{
		for (addressDataPair j : *_block)
		{
			switch (printOption)
			{
			case ('x'):
				sprintf(line, "0x%08x, 0x%08x\n", j.first, j.second);				
				writeFileStream << line;

				break;
			case ('b'):
				lineStr = "0b" + std::bitset<32>(j.first).to_string() + ", 0b" + std::bitset<32>(j.second).to_string() + '\n';
				writeFileStream << lineStr;

				break;
			case ('d'):
				sprintf(line, "0d%010d, 0d%010d\n", j.first, j.second);
				writeFileStream << line;

				break;
			default:
				sprintf(line, "0x%08x, 0x%08x\n", j.first, j.second);
				writeFileStream << line;
			}
		}
	}
	else
	{
		printf("unable to open file");
	}
}

int memory::read_from_memory(size_t address)
{
	return (*_block)[address];
}

void memory::write_to_memory(addressDataPair* data)
{
	if(!points_to_constant(data->first))
		(*_block)[data->first] = data->second;
}

memory::memory()
{
	_block = new std::map<size_t,int>();
	_sectionAddresses = new sectionAddresses();
	_size = 0;
	fs::path* wF = new fs::path(u8"bin/RAWRS_write.txt");
	fs::path* iF = new fs::path(u8"bin/RAWRS_init.txt");
	_writeFile = wF;									//by default the writeFile will be RAWRS_write
	_initFile = iF;										//by default the initFile will be RAWRS_init
	_constantAddresses = new std::set<size_t>();

}

memory::memory(std::map<size_t, int>* b, sectionAddresses* sA, size_t s, fs::path* wF, fs::path* iF, std::set<size_t>* cA)
{
	_block = b;
	_sectionAddresses = sA;
	_size = s;
	_writeFile = wF;
	_initFile = iF;
	_constantAddresses = cA;
}

memory::~memory()
{
	delete[]_block;
	delete[]_sectionAddresses;
	delete[]_writeFile;
	delete[]_initFile;

	printf("obj destroyed");
}

void memory::set_writeFile(fs::path* wF)
{
	_writeFile = wF;
}

fs::path* memory::get_writeFile()
{
	return _writeFile;
}

void memory::set_initFile(fs::path* iF)
{
	_initFile = iF;
}

fs::path* memory::get_initFile()
{
	return _initFile;
}

void memory::set_sectionAddresses(sectionAddresses* sA)
{
	_sectionAddresses = sA;
}

bool memory::is_address_valid(size_t address, char* section)
{
	// get position of section in sectionAddresses
	for (auto sec = _sectionAddresses->begin(); sec != _sectionAddresses->end(); ++sec)
	{
		if (!strcmp(sec->first, section))
		{
			// check if address is in range 
			return address >= sec->second && (
				sec == _sectionAddresses->end() - 1 ?
				this->is_address_valid(address) :
				address < (sec + 1)->second );
		}
	}

	return this->is_address_valid(address);
}

bool memory::is_address_valid(size_t address)
{
	return address >= 0 && address < _size;
}

memory::memory(size_t size, fs::path* init_file, fs::path* write_file) : memory()
{
	_size = size;
	set_initFile(init_file);
	set_writeFile(write_file);
}

void memory::set_constantAddresses(size_t address, int constants)
{
	std::pair<size_t, int>* temp = new std::pair<size_t, int>(address, constants);
	write_to_memory(temp); //AW: sets in memory
	_constantAddresses->insert(address);
}

bool memory::points_to_constant(size_t address)
{
	return _constantAddresses->find(address) != _constantAddresses->end();
}
