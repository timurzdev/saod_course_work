#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Handler {
private:
	struct record
	{
		char fullName[30]; //30 bytes
		int number; //4 bytes
		char position[22]; //22 bytes
		char birth_date[10]; //10 bytes
	};
	int lenght;
	record* records_array = new record[4000];
public:
	Handler() {
		lenght = 0;
	}
	~Handler() {
		delete[] records_array;
	}
	bool GetDataFromFile(char* filename) {
		char fullName_t[30];
		int number_t;
		char position_t[22];
		char birth_date_t[10];
		char buff;
		int struct_array_index = 0;
		char* memblock;
		int size;
		std::streampos begin, end;
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			std::cout << "Error opening file..." << std::endl;
			return false;
		}
		else std::cout << "Success " << std::endl;
		if (file.is_open()) {
			begin = file.tellg();
			file.seekg(0, std::ios::end);
			end = file.tellg();
			size = int(end - begin);
			std::cout << "size is: " << size << " bytes." << std::endl;
			memblock = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(memblock, size);
			file.close();
		}
		//filling struct

		delete[] memblock;
	}
	char* StringToCharArray(std::string string) {
		char* char_array = new char[string.size() + 1];
		strcpy_s(char_array, string.size()+1, string.c_str());
		return char_array;
	}
	void PrintStruct() {
		std::cout << this->records_array[0].fullName << std::endl;
	}
	
};