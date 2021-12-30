#pragma once
#include <string>
using namespace std;

struct BTNode {
	string data; // word from file or entered by user
	int count; // number of occurrences of the word
	BTNode* left; // address of left child, if it exists
	BTNode* right; // address of right child, if it exists
	BTNode* parent; // address of parent (all nodes except the root)
};