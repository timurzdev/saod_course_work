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
	record* records_array;
	record** records_index_array;

	record** GetIndexArray() {
		records_index_array = new record * [4000];
		for (size_t i = 0; i < 4000; i++) {
			records_index_array[i] = &records_array[i];
		}
		return records_index_array;
	}

public:
	Handler() {
		records_array = nullptr;
		records_index_array = nullptr;
	}
	~Handler() {
		delete[] records_array;
		delete[] records_index_array;
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
				this->records_array = GetDataFromFile(filename);
				this->records_index_array = GetIndexArray();
				break;
			case 2:
				size_t page;
				std::cout << "Input page number(1 - 200)" << std::endl;
				std::cin >> page;
				if (page < 1 || page >200) {
					break;
				}
				PrintStruct(page);
				break;
			default:
				break;
			}
		}
	}

	record* GetDataFromFile(char* filename) {
		this->records_array = new record[4000];
		size_t index = 0;
		record tmp{};
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			std::cout << "Error opening file..." << std::endl;
			return records_array;
		}
		else {
			while (file.read((char*)(&tmp), sizeof(record))) {
				records_array[index] = tmp;
				index++;
				if (index >= 4000) {
					break;
				}
			}
		}
		return records_array;
	}

	void PrintStruct(size_t page) {
		std::cout << std::endl;
		system("CLS");
		size_t start = (page-1) * 20;
		size_t end = start + 20;
		if (end > 4000) {
			std::cout << "Out of range " << std::endl;
			return;
		}
		int check;
		for (size_t i = start; i < end; i++) {
			std::cout.width(5);
			std::cout << i + 1;
			std::cout.width(30);
			std::cout << this->records_index_array[i]->fullName << " ";
			std::cout.width(5);
			std::cout << this->records_index_array[i]->number << " ";
			std::cout.width(22);
			std::cout << this->records_index_array[i]->position << " ";
			std::cout.width(10);
			std::cout << this->records_index_array[i]->birth_date << std::endl;
		}
		std::cout << "Print next 20? (1), previous 20? (0), exit (any other symbol) : ";
		std::cin >> check;
		if (check == 1) {
			if (page - 1 > 200) {
				std::cout << "Error..." << std::endl;
				return;
			}
			PrintStruct(page + 1);
		}
		else if (check == 0) {
			if (page - 1 < 1) {
				std::cout << "Error..." << std::endl;
				return;
			}
			PrintStruct(page - 1);
		}
		else {
			return;
		}
		//system("CLS");
		return;
	}
	
};