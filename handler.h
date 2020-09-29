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
		std::string text;
		int counter = 0;
		std::ifstream file(filename, std::ifstream::binary);
		if (!file) {
			std::cout << "Error reading file...";
			return false;
		}
		else {
			std::cout << "Success" << std::endl;
			for (file >> text; !file.eof(); file >> text)
				if (counter >= 100) {
					break;
				}
				else {
					//char* temp = StringToCharArray(text);
					std::cout << text << " " << std::endl;
					counter++;
					//delete[] temp;
				}
		}
		file.close();
		return true;
	}
	char* StringToCharArray(std::string string) {
		char* char_array = new char[string.size() + 1];
		strcpy_s(char_array, string.size()+1, string.c_str());
		return char_array;
	}
	
};