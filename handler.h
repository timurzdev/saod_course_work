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
	record* records_array = new record[4000];
	record** index_array = new record * [4000];
public:
	bool GetDataFromFile(char* filename) {
		std::ifstream file;
		std::string temp;
		file.open(filename);
		if (file.is_open()) {
			std::cout << " Success " << std::endl;
		}
		else {
			std::cout << "Can't open file " << std::endl;
			return false;
		}
		while (getline(file, temp)) {
			std::cout << temp << std::endl << std::endl;
		}
		return true;
	}
};