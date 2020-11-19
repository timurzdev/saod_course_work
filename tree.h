#ifndef TREE_H
#define TREE_H

#include "handler.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Tree {
private:
	Handler handler;
	std::vector<int> weightsSumArray;
	std::vector<Handler::record*>* records_index_array;
	struct weights {
		int weight = 0;
		Handler::record* data_ptr = nullptr;
	};
	std::vector<weights> weightsArray;
	std::vector<weights> weightsArrayClear;
	struct vertex {
		Handler::record* data_ptr = nullptr;
		int weight = 0;
		vertex* r_ptr = nullptr;
		vertex* l_ptr = nullptr;
	};
	vertex* root;
	size_t tree_size;
	vertex* tree_root;
	void createWeightsArray() {
		weightsArray.resize(30);
		Handler::node* temp = handler.queue_root;
		do {
			weightsArray[(temp->data.number) / 10].weight++;
			weightsArray[(temp->data.number) / 10].data_ptr = &temp->data;
			temp = temp->ptrNext;
		} while (temp->ptrNext != nullptr);
		for (size_t i = 0; i < weightsArray.size(); i++) {
			if (weightsArray[i].weight != 0) {
				weightsArrayClear.push_back(weightsArray[i]);
			}
		}
		weightsArray.clear();
	}
	void sortWeightsArray(int L, int R) {
		int i = L;
		int j = R;
		int temp = weightsArrayClear[(i + j) / 2].data_ptr->number;
		while (i <= j) {
			while (weightsArrayClear[i].data_ptr->number < temp) {
				i++;
			}
			while (weightsArrayClear[j].data_ptr->number > temp) {
				j--;
			}
			if (i <= j) {
				std::swap(weightsArrayClear[j], weightsArrayClear[j]);
				i++;
				j--;
			}
		}
		if (L < j) {
			sortWeightsArray(L, j);
		}
		if (i < R) {
			sortWeightsArray(i, R);
		}
	}
	void printLeftToRight(vertex* root) {
		if (root != nullptr) {
			printLeftToRight(root->l_ptr);
			std::cout << "     " << root->weight << " - ";
			handler.print1(root->data_ptr);
			printLeftToRight(root->r_ptr);
		}
	}

	void printTopToBottom(vertex* root) {
		if (root != nullptr) {
			std::cout << "     " << root->weight << " - ";
			handler.print1(root->data_ptr);
			printTopToBottom(root->l_ptr);
			printTopToBottom(root->r_ptr);
		}
	}
	void createWeightsSumArray() {
		sortWeightsArray(0, weightsArrayClear.size() - 1);
		weightsSumArray.push_back(0);
		for (size_t i = 1; i <= weightsArrayClear.size(); i++) {
			weightsSumArray.push_back(weightsArrayClear[i - 1].weight + weightsSumArray[i - 1]);
		}
	}
	static void addDoubleIndirection(weights* key, vertex** root) {
		vertex** head_ptr = root;
		while (*head_ptr) {
			if (key->data_ptr->number < (*head_ptr)->data_ptr->number) {
				head_ptr = &(*head_ptr)->l_ptr;
			}
			else if (key->data_ptr->number > (*head_ptr)->data_ptr->number) {
				head_ptr = &(*head_ptr)->r_ptr;
			}
			else {
				break;
			}
		}
		if (*head_ptr == nullptr) {
			*head_ptr = new vertex;
			(*head_ptr)->data_ptr = key->data_ptr;
			(*head_ptr)->weight = key->weight;
		}
	}
	int binaryIfSearch(int L, int R, double weight) {
		int mid = 0;
		int left = L;
		int right = R;
		while (L < R) {
			mid = (L + R) / 2;
			if ((double)(weightsSumArray[mid] - weightsSumArray[left]) < weight / 2
				&& (double)(weightsSumArray[mid] - weightsSumArray[left] + weightsArrayClear[mid].weight) > weight / 2) {
				return mid;
			}
			else
			{
				if ((double)(weightsSumArray[mid] - weightsSumArray[left]) < weight / 2
					&& !(double)(weightsSumArray[mid] - weightsSumArray[left] + weightsArrayClear[mid].weight) > weight / 2) {
					L = mid + 1;
				}
				else {
					R = mid - 1;
				}
			}
		}
	}


	void buildTree(vertex** root, int L, int R) {
		int left = L;
		int right = R;
		double weight;
		int temp_index;
		if (left <= right) {
			weight = (double)(weightsSumArray[right + 1] - weightsSumArray[left]);
			temp_index = binaryIfSearch(L, R, weight);
			addDoubleIndirection(&weightsArrayClear[temp_index], root);
			buildTree(root, left, temp_index - 1);
			buildTree(root, temp_index + 1, right);
		}
	}

	void deleteTree(vertex* root) {
		if (root == nullptr) {
			return;
		}
		else {
			deleteTree(root->l_ptr);
			deleteTree(root->r_ptr);
			delete root;
		}
	}
public:
	Tree() {
		root = nullptr;
		tree_root = nullptr;
		tree_size = 0;
		records_index_array = &handler.records_index_array;
		weightsArray.resize(30);
	}
	~Tree() {
		if (tree_root) {
			root = tree_root;
			deleteTree(root->l_ptr);
			deleteTree(root->r_ptr);
			tree_root = nullptr;
			delete root;
		}
		weightsArrayClear.clear();
		weightsSumArray.clear();
	}
	void Menu() {
		while (true) {
			system("cls");
			std::cout << std::endl;
			int menu;
			char filename[] = "testBase2.dat";
			std::cout << "0 - exit menu " << std::endl;
			std::cout << "1 - load data " << std::endl;
			std::cout << "2 - print data " << std::endl;
			std::cout << "3 - sort data " << std::endl;
			std::cout << "4 - search and create queue " << std::endl;
			std::cout << "5 - print queue " << std::endl;
			std::cout << "6 - build tree " << std::endl;
			std::cout << "7 - print tree " << std::endl;
			std::cout << "Input here: ";
			std::cin >> menu;
			std::cout << std::endl;
			switch (menu) {
			case 0:
				return;
			case 1:
				handler.records_array.clear();
				handler.records_index_array.clear();
				(*records_index_array).clear();
				handler.GetDataFromFile(filename);
				handler.GetIndexArray();
				break;
			case 2:
				size_t page;
				std::cout << "Input page number(1 - 200)" << std::endl;
				std::cin >> page;
				if (page < 1 || page > 200) {
					break;
				}
				handler.PrintStruct(page);
				break;
			case 3:
				handler.QuickSort(0, (*records_index_array).size() - 1);
				break;
			case 4:
				handler.createQueue();
				break;
			case 5:
				handler.printQueue();
				break;
			case 6:
				weightsArray.clear();
				weightsArrayClear.clear();
				if (tree_root) {
					root = tree_root;
					deleteTree(root->l_ptr);
					deleteTree(root->r_ptr);
					tree_root = nullptr;
					delete root;
				}
				createWeightsArray();
				createWeightsSumArray();
				buildTree(&tree_root, 0, weightsArrayClear.size() - 1);
				break;
			case 7:
				std::cout << "Left to Right: " << std::endl;
				printLeftToRight(tree_root);
				std::cout << std::endl << "Top to Bottom: " << std::endl;
				printTopToBottom(tree_root);
				std::cin.get();
				std::cin.ignore();
				break;
			default:
				break;
			}
		}
	}
};

#endif