#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		return std::cout << "Program needs TWO arguments, input and output!" << std::endl, 2;
	}

	std::string in(argv[1]), out(argv[2]);
	std::ifstream inFile(in);

	if (!inFile)
	{
		return std::cout << "Cannot read input file '" << in << "'" << std::endl, 3;
	}

	std::string data;
	inFile >> data;

	if (!inFile)
	{
		return std::cout << "Input file '" << in << "' corrupted!" << std::endl, 4;
	}

	//Decrypt

	return 0;
}