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
		else if (pos == -1) {
			std::cerr << "ifs.tellg() returned -1." << std::endl;
		} else {
            std::vector<char> result(pos);

            ifs.seekg(0, std::ios::beg);
            ifs.read(&result[0], pos);

            return result;
        }

	}
	else {
		std::cerr << "File was not opened" << std::endl;
		exit(1);
	}

    return {};
}

int WriteToFile(const std::vector<char>& FileBytes) {

	std::ofstream ofs;
	ofs.open("out.txt", std::ios::binary | std::ios::out);
	for (char FileByte : FileBytes) {
		ofs << FileByte;
	}
	ofs.close();
	return 0;

}

std::string BytesToHex(const std::vector<char>& FileBytes) {

	std::stringstream ss;
	std::string HexString;

	ss << std::hex << std::setfill('0');
	
	for (char FileByte : FileBytes)
	{
		ss << std::setw(2) << static_cast<unsigned>(FileByte);
	}

	HexString = ss.str();

	return HexString;

}

int PrettyTerminalOutput(std::string OutputString, std::vector<char> FileBytes) {
	
	unsigned long int hex_string_len = OutputString.length();
    unsigned long int bytes_vec_size = FileBytes.size();
	std::cerr << "Output string len is " << hex_string_len << std::endl;

    // let's insert spaces before iterating

    std::string hex_string;
    std::string bytes_string;

    std::vector<std::string> hex_string_vec = {};
    std::vector<std::string> bytes_string_vec = {};

    for (size_t i = 0; i < hex_string_len; i++) {
        hex_string += OutputString[i];
        if (i % 2 == 0) {
            hex_string += " ";
        }
        if (i % 32 == 0) {
            hex_string_vec.push_back(hex_string);
            hex_string = "";
        }
    }

    for (size_t i = 0; i < bytes_vec_size; i++) {

        // if ASCII code is less than 32 - that is control symbol
        // we don't have to display them
        if (FileBytes[i] < 32) {
            bytes_string += ".";
        } else {
            bytes_string += FileBytes[i];
        }

        if (i % 16 == 0) {
            bytes_string_vec.push_back(bytes_string);
            bytes_string = "";
        }
    }

    // don't lose data in case of i not %64 at the end of string
    hex_string_vec.push_back(hex_string);
    hex_string = "";

    std::cerr << hex_string_vec.size() << std::endl;
    std::cerr << bytes_string_vec.size() << std::endl;

    for (size_t i = 0; i < hex_string_vec.size(); i++) {
        std::cout << hex_string_vec[i] << "\t" << bytes_string_vec[i] << std::endl;
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

	PrettyTerminalOutput(HexString, FileBytes);

	return 0;

}