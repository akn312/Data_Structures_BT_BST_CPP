#include <iostream>
#include <fstream>
#include "NodeTypes.h"
#include "BinarySearchTree.cpp"
#include <vector>

using namespace std;

//Forward Declerations
BTNode* CreateBSTfromFile(BTNode*, string);
void AddWordtoBST(BTNode*);
void DeleteWordfromBST(BTNode*);
void SearchforWordinBST(BTNode*);
void TraverseBST(BTNode*);
void WhatComesBefore(BTNode*);
void WhatComesAfter(BTNode*);
void CompareBSTs(BTNode*);
void Stats(BTNode*);
int TotalNodes(BTNode*);
void SmallestBiggestWord(BTNode*);
void Weight(BTNode*);
void width(BTNode*);
void height(BTNode*);
void Totalnodes(BTNode*);
void Quit();

//Function to display the menu
int MainMenu(BTNode* root)
{
	int option;
	cout << "\nBinary Search Tree (BST)\n";
	cout << "---------------------------------------------\n\n";
	cout << "1. Create BST from File\n";
	cout << "2. Add Word to BST\n";
	cout << "3. Delete Word from BST\n";
	cout << "4. Search for Word in BST\n";
	cout << "5. Traverse BST\n";
	cout << "6. What Comes before Word in BST?\n";
	cout << "7. What Comes After Word in BST?\n";
	cout << "8. Compare BSTs\n";
	cout << "9. Statistics\n";
	cout << "Q. Quit\n\n";
	cout << "Please enter an option: "<<endl;
	cin >> option;

	switch (option)
	{
	case 1:
		root = CreateBSTfromFile(*&root, "Please enter the name of the file or M(Menu):");
		MainMenu(root);
	case 2:
		AddWordtoBST(root);
		MainMenu(root);
	case 3:
		DeleteWordfromBST(*&root);
		MainMenu(root);
	case 4:
		SearchforWordinBST(root);
		MainMenu(root);
	case 5:
		TraverseBST(root);
		MainMenu(root);
	case 6:
		WhatComesBefore(root);
		MainMenu(root);
	case 7:
		WhatComesAfter(root);
		MainMenu(root);
	case 8:
		CompareBSTs(root);
		MainMenu(root);
	case 9:
		Stats(root);
		MainMenu(root);
	default:
		Quit();
	}
	return option;
}

//Entry point
int main()
{
	BTNode* root = NULL;
	int ret = 0;
	int option = MainMenu(root);

	
	return ret;
}
//call for exiting
void Quit()
{
	exit(0);
}

//creates a BST from an input text file :- pass full path
BTNode* CreateBSTfromFile(BTNode *root, string message = "Please enter the name of the file or M(Menu): ")
{
	BTNode* BST = NULL;
	string option;
	cout << message << endl;
	cin >> option;
	if (option.compare("M") == 0)
	{
		main();
	}
	else
	{
		ifstream inputFile;		
		inputFile.open(option);
		if (!inputFile)
			cout << " Error opening file. " << endl;
		else
		{
			//variables used to load data into the tree
			string word;
			while (inputFile >> word)
			{
				BST = BinarySearchTree::ccreateBSTNode(root, word);
			}
		}
	}
	return BST;
}

//Adds a word to the BST by creating a new node
void AddWordtoBST(BTNode *parent)
{
	string option;
	cout << "Please enter the word to insert in the BST or M(Menu):" << endl;
	cin >> option;
	if (option.compare("M") == 0)
	{
		main();
	}
	else
	{		
		BinarySearchTree::insert(parent, option);
	}
}

//Deletes a word and the containing node
void DeleteWordfromBST(BTNode* parent)
{
	BTNode* NewRoot = NULL;
	string option;
	cout << "Please enter the word to delete from the BST or M(Menu) : " << endl;
	cin >> option;
	if (option.compare("M") == 0)
	{
		main();
	}
	else
	{
		parent = BinarySearchTree::deleteNode(parent, option);
	}
}

//Looks for a word in the BST
void SearchforWordinBST(BTNode* parent)
{
	string option;
	cout << "Please enter a word to search for or M (Menu): " << endl;
	cin >> option;
	if (option.compare("M") == 0)
	{
		main();
	}
	else
	{
		BTNode* NodeFound = NULL;
		NodeFound = BinarySearchTree::search(parent, option);
		if (NodeFound != NULL)
		{
			cout << "The word was found" << endl;
		}
		else
		{
			cout << "The word was not found" << endl;
		}

	}
}

//Travesrses the BST in pre-order and prints the containing words in the console
void TraverseBST(BTNode* parent)
{
	string * names = BinarySearchTree::preOrder(parent);	
	cout <<  names[0] << endl;	
	free(names);
}

//Outputs the word from the node before the node containing the input word
void WhatComesBefore(BTNode* parent)
{
	string option;
	cout << "Please enter a word to to find the word before it : " << endl;
	cin >> option;
	BTNode* pre = NULL;
	BTNode* NodeFound = NULL;
	NodeFound = BinarySearchTree::search(parent, option);
	if (NodeFound != NULL)
	{
		pre = BinarySearchTree::inOrderPredecessor(parent, NodeFound);
		if (pre != NULL)
		{
			cout << pre->data << endl;;
		}
	}
}

//Outputs the word from the node after the node containing the input word
void WhatComesAfter(BTNode* parent)
{
	string option;
	cout << "Please enter a word to to find the word after it : " << endl;
	cin >> option;
	BTNode* pre = NULL;
	BTNode* suc = NULL;
	BinarySearchTree::findPreSuc(parent, pre, suc, option);
	if (suc != NULL)
	{
		cout << suc->data << endl;
	}
}

//Compares 2 BSTs and outputs whether its identical or not
void CompareBSTs(BTNode* parent)
{
	bool ret = false;
	string option;
	BTNode* root2 = NULL;
	root2 = CreateBSTfromFile(root2,"Please enter the name of the file to create the BST or M (Menu):");
	if(root2!=NULL)
	{
		ret = BinarySearchTree::isEqual(parent, root2);
	}
	if (ret)
	{
		cout << "The files are same" << endl;
	}
	else
	{
		cout << "The files are not same" << endl;
	}
}

//provides the statstics pertaining to BST
void Stats(BTNode* parent)
{
	cout << "(1) Total Nodes :" << TotalNodes(parent) << endl;
	height(parent);
	width(parent);
	Weight(parent);
	SmallestBiggestWord(parent);
}

//Outputs the total number of nodes in BST
int TotalNodes(BTNode* root)
{
	int totalnodes = 0;
	if (root == NULL)
		return 0;

	//recursive call to left child and right child and
	// add the result of these with 1 ( 1 for counting the root)
	return 1 + TotalNodes(root->left) + TotalNodes(root->right);
}

//Outputs the depth level of the tree 
void height(BTNode* root)
{
	cout << "(2)The height of the tree.:" << BinarySearchTree::height(root) << endl;
}

//Returns the width of the binary tree. 
//The width of a binary tree is the maximum number of nodes at any level of the tree
void width(BTNode* root)
{
	cout << "(3)The width of the tree:" << BinarySearchTree::width(root)<< endl;
}

//The weight of a binary tree is the amount of leaves in the tree
void Weight(BTNode* root)
{
	cout << "(4)The weight of the tree." << BinarySearchTree::weight(root)<<endl;
}

//Finds the smallest and the biggest word in the BInarySearchTree but in alphabetical 
//order and not length wise
void SmallestBiggestWord(BTNode* root)
{
	cout << "(5)The smallest word is :" << BinarySearchTree::minValueNode(root)->data <<"\n  and the biggest word (in alphabetical order) stored in the tree is: " << BinarySearchTree::maxValue(root)<< endl;
}

