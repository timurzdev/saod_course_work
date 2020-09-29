#pragma once
#include <iostream>
#include <fstream>

class Handler {
private:
	struct record
	{
		char fullName[30]; //30 bytes
		unsigned short int number; //2 bytes
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
	unsigned short int BytesToInt(unsigned char* buff) {
		unsigned short int a = (unsigned short int)((buff[0]) << 8 |
			(buff[1]) << 0);
		return a;
	}
	bool GetDataFromFile(char* filename) {
		char fullName_t[30];
		unsigned short int number_t;
		char position_t[22];
		char birth_date_t[10];
		char* memblock;
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
			//delete memblock
			//delete[] memblock;
			file.close();

		}
		return true;
	}

	void PrintStruct() {
		std::cout << std::endl;
		for (size_t i = 3900; i < 4000; i++) {
			std::cout.width(30);
			std::cout << this->records_array[i].fullName << " ";
			std::cout.width(10);
			std::cout << this->records_array[i].number << " ";
			std::cout.width(22);
			std::cout << this->records_array[i].position << " ";
			std::cout.width(10);
			std::cout << this->records_array[i].birth_date << std::endl;
		}
		
	}
	
};