#include <iostream>
#include <fstream>
#include <sstream>
// #include <windows.h>
#include <vector>
#include <string>
#include <iomanip>


std::vector<char> ReadBinaryFile(const std::string& filename) {

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

int WriteToFile(std::vector<char> FileBytes) {

	std::ofstream ofs;
	ofs.open("out.txt", std::ios::binary | std::ios::out);
	for (unsigned long long int i = 0; i < FileBytes.size(); i++) {
		ofs << FileBytes[i];
	}
	ofs.close();
	return 0;

}

int WriteToTerminal(std::vector<char> FileBytes) {

	for (unsigned long long int i = 0; i < FileBytes.size(); i++) {
		std::cout << FileBytes[i];
	}
	return 0;

}

std::string BytesToHex(std::vector<char> FileBytes) {
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

int PrettyTerminalOutput(std::string OutputString) {
	
	unsigned long int string_len = OutputString.length();
	std::cerr << "Output string len is " << string_len;

    // let's insert spaces before iterating

    std::string pretty_string;
    std::vector<std::string> pretty_string_vec = {};
    for (size_t i = 0; i < string_len; i++) {
        pretty_string += OutputString[i];
        if (i % 2 == 0) {
            pretty_string += " ";
        }
        if (i % 64 == 0) {
            pretty_string_vec.push_back(pretty_string);
            pretty_string = "";
        }
    }

    // don't lose data in case of i not %64 at the end of string
    pretty_string_vec.push_back(pretty_string);
    pretty_string = "";

    std::cerr << pretty_string_vec.size();

    for (size_t i = 0; i < pretty_string_vec.size(); i++) {
        std::cout << pretty_string_vec[i] << std::endl;
    }

	return 0;

}

int main() {

	std::string filepath;

	std::cout << "Enter filepath:" << std::endl;
	std::cout << "> ";
	std::cin >> filepath;

	std::vector<char> FileBytes = ReadBinaryFile(filepath);

	WriteToFile(FileBytes);
	std::string HexString = BytesToHex(FileBytes);

	PrettyTerminalOutput(HexString);

	return 0;

}