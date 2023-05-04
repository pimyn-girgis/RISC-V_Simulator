#pragma once

#ifndef MEMORY_H
#define	MEMORY_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <filesystem>	//	AW: supposedly cross platform, (C++ 17)+ standard, paths covertible to string so this is very neat
#include <bitset>

#define	 addressDataPair	std::pair<int,int>
#define	 addressDataPairs	std::vector<std::pair<int, int>*>
#define	 sectionAddresses	std::map<char*, int>

namespace fs = std::filesystem;

/// AW:	memory class responsible for encapsulating the memory and its methods
///		has built in support for sectioning memory 
///		
///		FFR	may be used to make/instantiate the register class/object instead of hardcoding them
///		register class inherits the basic functions from the memory such as printing/etc
///		register object has empty section map
///		
///		What it should do as a blackbox:	
///		>	write to memory (done)
///		>	read from memory (done)
///		>	you can section it off, etc (wip)
///		>	check which section your address belongs to (wip)
///		>	print on .txt, console (done) (will need modifications for sectioning, honestly could be left as is but
///			i want pretty printing with section labels above their addresses, which will also help in GUI)
///		>	anything else?
class memory
{
private:
	std::map<int, int>*				_block;							//	AW: memory block, address as key, data as value
	sectionAddresses*				_sectionAddresses;				//	AW: section labels, string is label .i.e .data and key, address as the value

	long long int					_size;							///	AW: i.e. 4GB has 0d1073741824 addressable 32bit words, or 0x40000000 in hex. so 
																	///	this is initialized as the last addressable address in the memory
																	/// will be useful for validation

	fs::path*						_writeFile;						//	AW: default file path for writing
	fs::path*						_initFile;						//	AW: default file path for initialisations

public:

	memory();
	memory(std::map<int, int>* block, sectionAddresses* sA, long int size, fs::path* writeFile, fs::path* initFile);
	~memory();

	void					set_writeFile(fs::path* writeFile);
	fs::path*				get_writeFile();
	void					set_initFile(fs::path* initFile);
	fs::path*				get_initFile();
	void					set_sectionAddresses(sectionAddresses*);

	/// AW: setters, getters used for GUI 
	/// I am thinking for GUI we have a seperate memory GUI utilties file to output what we need in Qt using
	/// some mini functions or some shit idk I will figure it out
	/// 
	/// inits, printers, writers used for CLI
	
	//	AW: parses text file, final output in an array of pair pointers, given a file path
	addressDataPairs*		parse_init_file();

	/// AW: Initializes memory given parsed memory initializations
	///	parsed initializations stored in an array of pair pointers  
	void					init_memory(addressDataPairs*);

	//	AW: writes given data to memory block member given address and data in a pair
	void					write_to_memory(addressDataPair*);

	//	AW: reads data given an address (basically a getter for data)
	int						read_from_memory(int);
	
	///	AW: CLI
	///	print option: according to the char we print in Hex, Dec
	/// prints memory on console lol 
	void					print_memory(char printOption);

	///	AW: CLI
	/// print option: according to the char we print in Hex, Dec
	///	writes to file path (member)
	void					write_memory_to_file(char printOption);

	bool					is_address_valid(int address, char* section);

	bool					is_address_valid(int address);					//AW: for sectionless memory (in our case


};

#endif