#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

class Handler {
private:
	struct record
	{
		char fullName[30]; //30 bytes
		short int number; //2 bytes
		char position[22]; //22 bytes
		char birth_date[10]; //10 bytes
		
	};

	std::string static new_date(const char date[]){
	    char temp_day[2];
	    char temp_month[2];
	    char temp_year[2];
	    temp_day[0] = date[0];
	    temp_day[1] = date[1];
	    temp_month[0] = date[3];
	    temp_month[1] = date[4];
	    temp_year[0] = date[6];
	    temp_year[1] = date[7];
	    std::string temp = temp_year;
	    temp += temp_month;
	    temp += temp_year;
	    return temp;
	}

	friend bool operator<(const record& node1, const record& node2) {
		if (( new_date(node1.birth_date) == new_date(node2.birth_date))) {
			return (strcmp(node1.fullName, node2.fullName) < 0);
		}
		else {
			return new_date(node1.birth_date) < new_date(node2.birth_date);
		}
	}

    friend bool operator>(const record& node1, const record& node2) {
        if (( new_date(node1.birth_date) == new_date(node2.birth_date))) {
            return (strcmp(node1.fullName, node2.fullName) > 0);
        }
        else {
            return new_date(node1.birth_date) > new_date(node2.birth_date);
        }
    }

	std::vector <record> records_array;
	std::vector <record*> records_index_array;

	void GetIndexArray() {
		for (size_t i = 0; i < 4000; i++) {
			records_index_array.push_back(&records_array[i]);
		}
		return;
	}

	

	void PrintHeading() {
		std::cout.width(10);
		std::cout << "Index";
		std::cout.width(30);
		std::cout << "FullName";
		std::cout.width(10);
		std::cout << "Number";
		std::cout.width(22);
		std::cout << " Position ";
		std::cout.width(15);
		std::cout << "     Birth Date";
		std::cout << std::endl;
	}
	void GetDataFromFile(char* filename) {
		record tmp{};
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			std::cout << "Error opening file..." << std::endl;
			return;
		}
		else {
			while (file.read((char*)(&tmp), sizeof(record))) {
				this->records_array.push_back(tmp);
			}
		}
		return;
	}
	void swap(record** first, record** second) {
		record* temp = *first;
		*first = *second;
		*second = temp;
		return;
	}

	void QuickSort(int L, int R) {
		int i = L;
		int j = R;
		record temp = *records_index_array[(i + j) / 2];

		while (i <= j) {
			while (*records_index_array[i] < temp) {
				i++;
			}
			while (*records_index_array[j] > temp) {
				j--;
			}
			if (i <= j) {
				swap(&records_index_array[i], &records_index_array[j]);
				i++;
				j--;
			}
		}
		if (L < j) {
			QuickSort(L, j);
		}
		if (i < R) {
			QuickSort(i, R);
		}
		return;
	}

	void PrintStruct(size_t page) {
		std::cout << std::endl;
		system("clear");
		size_t start = (page - 1) * 20;
		size_t end = start + 20;
		int check;
		if (end > 4000) {
			std::cout << "Out of range " << std::endl;
			return;
		}
		PrintHeading();
		for (size_t i = start; i < end; i++) {
			std::cout.width(10);
			std::cout << i + 1;
			std::cout.width(30);
			std::cout << this->records_index_array[i]->fullName << " ";
			std::cout.width(10);
			std::cout << this->records_index_array[i]->number << " ";
			std::cout.width(22);
			std::cout << this->records_index_array[i]->position << " ";
			std::cout.width(15);
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
		return;
	}
public:
	Handler() {
	}
	~Handler() {
		records_array.clear();
		records_index_array.clear();
	}
	
	void Menu() {
		while (true) {
			std::cout << std::endl;
			int menu;
			char filename[] = "../testBase2.dat";
			std::cout << "0 - exit menu " << std::endl;
			std::cout << "1 - load data " << std::endl;
			std::cout << "2 - print data " << std::endl;
			std::cout << "3 - sort data " << std::endl;
			std::cout << "Input here: ";
			std::cin >> menu;
			std::cout << std::endl;
			switch (menu)
			{
			case 0:
				return;
			case 1:
				GetDataFromFile(filename);
				GetIndexArray();
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
			case 3:
				QuickSort(0, 4000-1);
				break;
			default:
				break;
			}
		}
	}


	
	
};