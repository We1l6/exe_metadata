#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

static std::vector<char> ReadAllBytes(char const* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	if (pos == 0) {
		return std::vector<char>{};
	} else {
		std::cerr << "ifs.tellg() returned -1. Check file!";
	}

	std::vector<char> result(pos);

	ifs.seekg(0, std::ios::beg);	
	ifs.read(&result[0], pos);

	return result;
}

int main() {

	char filepath[] = "";

	std::cout << "Enter filepath:" << std::endl;
	std::cout << "> " << std::endl;
	std::cin >> filepath;

	std::vector<char> FileBytes = ReadAllBytes(filepath);

	for (long long int i = 0; i < FileBytes.size(); i++) {
		std::cout << FileBytes[i];
	}

	return 0;
}