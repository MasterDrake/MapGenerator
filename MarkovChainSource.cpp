#include "MarkovChain/MarkovChain.h"

#include <fstream>
#include <iostream>

int main(int argc, char * argv[])
{
	std::vector<std::string> names;

	std::ifstream names_file;
	names_file.open("../../../Resources/names.txt", std::ios::in);

	if(!names_file.is_open())
		return 0;	

	std::string line;
	while(std::getline(names_file, line))
		names.emplace_back(std::move(line));

	MarkovChain mng(names, 3, 4);
	while(true)
	{
		std::cout << mng.getName() << std::endl;
		std::cin.get();
	}

	return 0;
}