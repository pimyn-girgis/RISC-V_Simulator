#pragma once

#ifndef MEMORY_H
#define	MEMORY_H

#include <iostream>
#include <map>
#include <vector>
#include <filesystem>	//	AW: supposedly cross platform, (C++ 17)+ standard, paths covertible to string so this is very neat

namespace fs = std::filesystem;

/// AW:	memory class responsible for encapsulating the memory and its methods
///		has built in support for sectioning memory 
///		
///		FFR	may be used to make/instantiate the register class/object instead of hardcoding them
///		register class inherits the basic functions from the memory such as printing/etc
///		register object has empty section map
///		
///		What it should does as a blackbox:	write to memory 
///											read from memory
///											initialize a memory object and you can section it off, etc
///											check which section your address belongs to 
///											print on .txt, console
///											

class memory
{
private:
	std::map<int, int>*				block;							//	AW: memory block, address as key, data as value
	std::map<std::string, int>*		sectionAddresses;				//	AW: section labels, string is label .i.e .data and key, address as the value

	long long int					size;							///	i.e 4GB has 0d1073741824 addressable 32bit words, or 0x40000000 in hex. so 
																	///	this is initialized as the last addressable address in the memory

	fs::path						writeFile;						//	AW: default file path for writing

public:

	memory();
	memory(std::map<int, int>* block, std::vector<int>* sectionAddresses, long int size, fs::path writeFile);

	void set_writeFile(fs::path writeFile);
	void get_writeFile(fs::path writeFile);

	/// AW: setters, getters used for GUI 
	/// I am thinking for GUI we have a seperate memory GUI utilties file to output what we need in Qt using
	/// some mini functions or some shit idk I will figure it out
	/// 
	/// inits, printers, writers used for CLI
	
	std::pair<int, int>** parse_init_file();			//	parses text file, final output in an array of pair pointers

	void init_memory(std::pair<int, int>** );			/// Initializes memory given parsed memory initializations
														///	parsed initializations stored in an array of pair pointers
											
	void print_memory(char printOption);				///	CLI
														///	print option: according to the char we print in Hex, Dec
														/// prints memory on console lol 

	void write_memory_to_file(char printOption);		///	CLI
														/// print option: according to the char we print in Hex, Dec
														///	writes to file path (member)

};

#endif