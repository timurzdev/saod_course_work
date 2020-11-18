#pragma once

#include "handler.h"
#include <iostream>
#include <vector>


class Tree {
private:
	Handler *local;
	std::vector<Handler::record*> records_index_array = local->records_index_array;
	Handler::node* queue_root = local->queue_root;
	std::vector<int> weightsSumArray;
	std::vector<int> weightsArray;
	struct vertex {
		vertex* r_ptr = nullptr;
		vertex* l_ptr = nullptr;
	};
public:
	Tree(Handler &object) {
		*local = object;
	}
	void getQueueRoot() {
		std::cout << "HUY" << std::endl;
	}
};