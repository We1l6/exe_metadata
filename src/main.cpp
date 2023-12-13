#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

static std::vector<char> ReadBinaryFile(char const* filename) {

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

static int WriteToFile(std::vector<char> FileBytes) {

	std::ofstream ofs;
	ofs.open("out.txt", std::ios::binary | std::ios::out);
	for (unsigned long long int i = 0; i < FileBytes.size(); i++) {
		ofs << FileBytes[i];
	}
	ofs.close();
	return 0;

}



static int WriteToTerminal(std::vector<char> FileBytes) {

	for (unsigned long long int i = 0; i < FileBytes.size(); i++) {
		std::cout << FileBytes[i];
	}
	return 0;

}

int main() {

	char filepath[] = "";

	std::cout << "Enter filepath:" << std::endl;
	std::cout << "> ";
	std::cin >> filepath;

	std::vector<char> FileBytes = ReadBinaryFile(filepath);

	WriteToFile(FileBytes);
	WriteToTerminal(FileBytes);

	return 0;

}