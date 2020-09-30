#pragma once
#include <iostream>
#include <fstream>

class Handler {
private:
	struct record
	{
		char fullName[30]; //30 bytes
		short int number; //2 bytes
		char position[22]; //22 bytes
		char birth_date[10]; //10 bytes
	};
	int lenght;
	record* records_array = new record[4000];
	record** records_index_array = new record * [4000];
public:
	Handler() {
		lenght = 0;
	}
	~Handler() {
		delete[] records_array;
		delete[] records_index_array;
	}
	short int BytesToInt(unsigned char* buff) {
		unsigned char high = buff[0];
		unsigned char low = buff[1];
		return high + (low & 0xFF >> (CHAR_BIT));
	}
	char* DeleteSpacesInString(char* string) {
		for (size_t i = 0; i < std::strlen(string); i++) {
			if (string[i] == ' ') {
				string[i] = '_';
			}
		}
		return string;
	}
	void DeleteSpacesInStruct() {
		for (size_t i = 0; i < 4000; i++) {
			strcpy_s(this->records_array[i].fullName, std::strlen(this->records_array[i].fullName) + 1, DeleteSpacesInString(this->records_array[i].fullName));
			strcpy_s(this->records_array[i].position, std::strlen(this->records_array[i].position) + 1, DeleteSpacesInString(this->records_array[i].position));
			strcpy_s(this->records_array[i].birth_date, std::strlen(this->records_array[i].birth_date) + 1, DeleteSpacesInString(this->records_array[i].birth_date));
		}
	}
	void Menu() {
		while (true) {
			std::cout << std::endl;
			int menu;
			char filename[] = "./Debug/testBase2.dat";
			std::cout << "0 - exit menu " << std::endl;
			std::cout << "1 - load data " << std::endl;
			std::cout << "2 - print data " << std::endl;
			std::cout << "Input here: ";
			std::cin >> menu;
			std::cout << std::endl;
			switch (menu)
			{
			case 0:
				return;
			case 1:
				GetDataFromFile(filename);
				DeleteSpacesInStruct();
				break;
			case 2:
				PrintStruct(0);
				break;
			default:
				break;
			}
		}
	}
	bool GetDataFromFile(char* filename) {
		if (this->records_array[0].number == 130) {
			std::cout << "data is already loaded" << std::endl;
			return false;
		}
		char fullName_t[30];
		unsigned short int number_t;
		char position_t[22];
		char birth_date_t[10];
		char* memblock;
		char* buff_string = new char[64];
		int size;
		unsigned char buff[4];
		int strlen;
		size_t memblock_index = 0;
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
			//filling struct
			for (size_t i = 0; i < 4000; i++) {
				this->records_index_array[i] = &this->records_array[i];
				for (size_t j = memblock_index, temp_index = 0; j < memblock_index + 30; j++, temp_index++ ) {
					fullName_t[temp_index] = memblock[j];
				}
				strlen = std::strlen(fullName_t);
				strcpy_s(this->records_array[i].fullName, strlen + 1, fullName_t);
				memblock_index += 30;
				for (size_t j = memblock_index, temp_index = 0; j < memblock_index + 2; j++, temp_index++) {
					buff[temp_index] = (unsigned char)memblock[memblock_index];
				}
				this->records_array[i].number = BytesToInt(buff);
				memblock_index += 2;
				for (size_t j = memblock_index, temp_index = 0; j < memblock_index + 22; j++, temp_index++) {
					position_t[temp_index] = memblock[j];
				}
				strlen = std::strlen(position_t);
				strcpy_s(this->records_array[i].position, strlen + 1, position_t);
				memblock_index += 22;
				for (size_t j = memblock_index, temp_index = 0; j < memblock_index + 10; j++, temp_index++) {
					birth_date_t[temp_index] = memblock[j];
				}
				strlen = std::strlen(birth_date_t);
				strcpy_s(this->records_array[i].birth_date, strlen + 1, birth_date_t);
				memblock += 10;
			}
			//for (size_t i = 0; i < 2; i++) {
			//	for (size_t j = memblock_index, temp_index = 0; j < memblock_index + 64; j++, temp_index++) {
			//		buff_string[temp_index] = memblock[memblock_index];
			//	}
			//	//fill_struct
			//	memblock_index += 64;
			//}
			file.close();
		}
		return true;
	}

	void PrintStruct(size_t start) {
		std::cout << std::endl;
		system("CLS");
		size_t end = start + 20;
		if (end >= 4000)
			return;
		int check;
		if (this->records_array[0].number != 130) {
			std::cout << "Array is empty " << std::endl;
			return;
		}
		for (size_t i = start; i < end; i++) {
			std::cout.width(30);
			std::cout << this->records_index_array[i]->fullName << " ";
			std::cout.width(10);
			std::cout << this->records_index_array[i]->number << " ";
			std::cout.width(22);
			std::cout << this->records_index_array[i]->position << " ";
			std::cout.width(10);
			std::cout << this->records_index_array[i]->birth_date << std::endl;
		}
		std::cout << "Print next 20? (1/0) : ";
		std::cin >> check;
		if (check) {
			PrintStruct(start + 20);
		}
		system("CLS");
		return;
	}
	
};