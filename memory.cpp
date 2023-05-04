
#include "memory.h"

//AW: i could parse and initialise immediately but i am chose to do it this way to so i have the parsed data accessible for the GUI
//AW: might put the return vector as member in the class w 5alas 

addressDataPairs* memory::parse_init_file()
{
	std::ifstream		initFileStream;
	std::string			line;
	int					data;
	int					address;
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
	for (std::pair<int, int>* j : *parsedPairs)
	{
		_block->insert(*j);
	}
}
													
void memory::print_memory(char printOption)
{
	for (std::pair<int, int> j : *_block)
	{
		switch (printOption)
		{
		case ('x'):
			printf("%x, %x\n", j.first, j.second);
			break;
		case ('b'):
			printf("%x, %x\n", j.first, j.second);
			break;
		case ('d'):
			printf("%d, %d\n", j.first, j.second);
			break;
		default:
			printf("%x, %x\n", j.first, j.second);
		}
	}
}
																									
void memory::write_memory_to_file(char printOption)
{

}

int memory::read_from_memory(int address)
{
	return (*_block)[address];
}

void memory::write_to_memory(addressDataPair* data)
{
	(*_block)[data->first] = data->second;
}

memory::memory()
{
	_block = new std::map<int,int>();
	_sectionAddresses = new std::map<std::string, int>();
	_size = 0;
	fs::path* wF = new fs::path(u8"\\RAWRS_write.txt");
	fs::path* iF = new fs::path(u8"\\RAWRS_init.txt");
	_writeFile = wF;				//by default the writeFile will be RAWRS_write
	_initFile = iF;				//by default the initFile will be RAWRS_init

}

memory::memory(std::map<int, int>* b, std::map<std::string, int>* sA, long int s, fs::path* wF, fs::path* iF)
{
	_block = b;
	_sectionAddresses = sA;
	_size = s;
	_writeFile = wF;
	_initFile = iF;
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
