#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <string>
#include <iomanip>

static std::vector<char> ReadBinaryFile(char const* filename) {

	// create input filestream
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);

	// check if ifs is open
	if (ifs.is_open()) {
		std::ifstream::pos_type pos = ifs.tellg();

		if (pos == 0) {
			return std::vector<char>{};
		}
		else {
			std::cerr << "ifs.tellg() returned -1." << std::endl;
		}

		std::vector<char> result(pos);

		ifs.seekg(0, std::ios::beg);
		ifs.read(&result[0], pos);

		return result;
	}
	else {
		std::cerr << "File was not opened" << std::endl;
		exit(1);
	}
	
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

static std::string BytesToHex(std::vector<char> FileBytes) {
	std::stringstream ss;
	std::string HexString;

	ss << std::hex << std::setfill('0');
	
	for (unsigned long long int i = 0; i < FileBytes.size(); ++i)
	{
		ss << std::setw(2) << static_cast<unsigned>(FileBytes[i]);
	}

	HexString = ss.str();

	return HexString;

}

static int PrettyTerminalOutput(std::string OutputString) {
	
	unsigned long int string_len = OutputString.length();
	std::string pretty_string;
	
	std::cerr << "Output string len is " << string_len;

	unsigned short int ps_len = 0;

	for (unsigned long long int i = 0; i < string_len; i += 1) {

		pretty_string = pretty_string + OutputString[i];
		ps_len = pretty_string.length();

		if (pretty_string.length() % 2 == 0) {
			pretty_string = pretty_string + " ";
		}

		if (pretty_string.length() % 16 == 0) {
			std::cout << pretty_string << std::endl;
			pretty_string = "";
		}

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
	std::string HexString = BytesToHex(FileBytes);

	PrettyTerminalOutput(HexString);

	return 0;

}