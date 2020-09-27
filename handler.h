#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Handler {
private:
	struct record
	{
		char fullName[30];
		int number;
		char position[22];
		char birth_date[10];
	};
	int lenght;
	char* buffer;
	record* records_array = new record[4000];
public:
	Handler() {
		lenght = 0;
		buffer = nullptr;
	}
	~Handler() {
		delete[] buffer;
	}
	bool GetDataFromFile(char* filename) {
		std::ifstream file(filename, std::ifstream::binary);
		if (file) {
			file.seekg(0, file.end);
			this->lenght = file.tellg();
			file.seekg(0, file.beg);
			this->buffer = new char[this->lenght];
			std::cout << "Reading " << this->lenght << " characters... ";
			file.read(this->buffer, this->lenght);
			if (file)
				std::cout << "all characters read successfully.\n";
			else {
				std::cout << "error: only " << file.gcount() << "could be read";
				return false;
			}
			file.close();
		}
		return true;
	}
};