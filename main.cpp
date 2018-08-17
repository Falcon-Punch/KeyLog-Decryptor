#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Global constants
const std::string &saltStr1 = "30//99:/WW";
const std::string &saltStr2 = "!falcon!!kong";
const std::string &saltStr3 = "_SOUL=*DARK::";
const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function prototypes
std::string decryptB64(std::string s);
std::string base64_decode(const std::string &s);

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

	decryptB64(data);

	std::ofstream outFile(out);

	if (!outFile)
	{
		return std::cout << "Cannot write output file '" << out << "'" << std::endl, 5;
	}
		
	outFile << data;

	std::cout << "Decoding was successful!" << std::endl;

	return 0;
}

std::string decryptB64(std::string str) 
{
	str = str.erase(9, 1);
	str = str.erase(5, 1);
	str = base64_decode(str);
	str = str.substr(saltStr1.length());
	str = base64_decode(str);
	str = str.substr(0, str.length() - saltStr2.length() - saltStr3.length() - saltStr1.length());
	str = str.substr(saltStr3.length());
	str = str.erase(3, saltStr3.length());
	str = base64_decode(str);
	str = str.substr(0, str.length() - saltStr1.length() - saltStr2.length() - saltStr3.length());

	return str;
}

std::string base64_decode(const std::string &str)
{
	std::string outStr;
	std::vector<int> vec(256, -1);

	for (int i = 0; i < 64; i++)
	{
		vec[BASE64_CODES[i]] = i;
	}
		
	int val = 0, bits = -8;

	for (const auto &charHolder : str)
	{
		if (vec[charHolder] == -1) { break; }

		val = (val << 6) + vec[charHolder];
		bits += 6;

		if (bits >= 0)
		{
			outStr.push_back(char((val >> bits) & 0xFF));
			bits -= 8;
		}
	}

	return outStr;
}