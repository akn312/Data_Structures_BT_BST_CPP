#include "NodeTypes.h"
#include <algorithm>
#include <stack>
#include <iostream>
#include "BinaryTree.cpp"

class BinarySearchTree : public BinaryTree
{
	//Creates a BSTNode in a BST
	public: static  BTNode* ccreateBSTNode(BTNode*& parent, string data)
	{
		// if the root is null, create a new node and return it
		if (parent == NULL) {
			parent = new BTNode;
			parent->data = data;
			parent->left = NULL;
			parent->right = NULL;
			parent->parent = NULL;
			parent->count = 1;
			return parent;
		}

		// if the given key is less than the root node, recur for the left subtree
		if (data < parent->data) {
			parent->left = ccreateBSTNode(parent->left, data);
		}
		// if the given key is more than the root node, recur for the right subtree
		else {
			parent->right = ccreateBSTNode(parent->right, data);
		}

		return parent;
	}

	//Returns the address of the node with the smallest key in the BST that is greater than
	//or equal to key, regardless if key is present in the BST.
	//Returns NULL if there is no such node.
	public: static BTNode* ceiling(BTNode* root, string key)
	{
		// Base case
		if (root == NULL)
			return NULL;

		BTNode* current = NULL;

		//loop down to find the leftmost leaf 
		while (current && current->left != NULL)
			current = current->left;

		return current;
	}

	//Removes the node containing the specified key (if key is present in the BST). 
	//Returns the address of the root of the tree without the deleted node.
	public: static BTNode* deleteNode(BTNode* root, string key)
	{
		// base case
		if (root == NULL)
			return root;

		// If the key to be deleted is
		// smaller than the root's
		// key, then it lies in left subtree
		if (key < root->data)
			root->left = deleteNode(root->left, key);

		// If the key to be deleted is
		// greater than the root's
		// key, then it lies in right subtree
		else if (key > root->data)
			root->right = deleteNode(root->right, key);

		// if key is same as root's key, then This is the node
		// to be deleted
		else {
			// node has no child
			if (root->left == NULL and root->right == NULL)
				return NULL;

			// node with only one child or no child
			else if (root->left == NULL) {
				struct BTNode* temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL) {
				BTNode* temp = root->left;
				free(root);
				return temp;
			}
			// node with two children: Get the inorder successor
			// (smallest in the right subtree)
			 BTNode* temp = minValueNode(root->right);

			// Copy the inorder successor's content to this node
			root->data = temp->data;

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->data);
		}
		return root;
	}

	//Given a non-empty binary search tree, return the node
	//with minimum key value found in that tree. Note that the
	//entire tree does not need to be searched.
	static BTNode* minValueNode(BTNode* node)
	{
		BTNode* current = node;

		/* loop down to find the leftmost leaf */
		while (current && current->left != NULL)
			current = current->left;

		return current;
	}

	//Returns the address of the node with the biggest key in the BST that is less than or equal to key,
	//regardless if key is present in the BST.Returns NULL if there is no such node.
	public: static BTNode* floor(BTNode* root, string key)
	{
		if (!root)
			return NULL;

		//If root->data is equal to key 
		if (root->data == key)
			return root;

		//If root->data is greater than the key
		if (root->data > key)
			return floor(root->left, key);

		//Else, the floor may lie in right subtree
			// or may be equal to the root
		BTNode* floorValue = floor(root->right, key);
		return (floorValue->data <= key) ? floorValue : root;
	}

	//Returns the in-order predecessor of the node supplied as a parameter. 
	//Returns NULL if the node is NULL or there is no in-order predecessor of the node.
	public: static BTNode* inOrderPredecessor(BTNode * root, BTNode* node)
	{
		BTNode* predecessor = NULL;
		BTNode* current = root;
		string val = node->data;

		if (!root)
			return NULL;

		while (current && current->data != val) {
			//Else take left turn and no need to update predecessor pointer
			if (current->data > val) {
				current = current->left;
			}
			//If node value is less than the node which are looking for, then go to right sub tree
			//Also when we move right, update the predecessor pointer to keep track of last right turn
			else {
				predecessor = current;
				current = current->right;
			}
		}
		if (current && current->left) {
			predecessor = findMaximum(current->left);
		}
		return predecessor;
	}

	//This function return the maximum node in tree rooted at node root * /
	static BTNode * findMaximum(BTNode* root) 
	{
		if (!root)
			return NULL;

		while (root->right) root = root->right;
		return root;
	}

	//If key is not already present, inserts key into the BSTand returns true.
	//If key is present, updates the count of keyand returns false.
	public: static bool insert(BTNode* root, string key)
	{
		bool ret = false;
		BTNode* node = ccreateBSTNode(root, key);
		if (node != NULL)
			ret = true;
		return ret;
	}
	
	//Returns a node with the data passed in the argument as key
	public: static BTNode* search(struct BTNode* root, string key)
	{
		// Base Cases: root is null or key is present at root
		if (root == NULL || root->data == key)
			return root;

		// Key is greater than root's key
		if (root->data < key)
			return search(root->right, key);

		// Key is smaller than root's key
		return search(root->left, key);
	}
	
	//This function return the maximum node in tree rooted at node root
	public: static string maxValue(struct BTNode* node)
	{
		BTNode* current = node;

		//loop down to find the rightmost leaf 
		while (current->right != NULL)
		{
			current = current->right;
		}
		return(current->data);
	}

	// This function finds predecessor and successor of data in BST.
	// It sets pre and suc as predecessor and successor respectively
	public: static void findPreSuc(BTNode* root, BTNode*& pre, BTNode*& suc, string data)
	{
		// Base case
		if (root == NULL)  return;

		// If key is present at root
		if (root->data == data)
		{
			// the maximum value in left subtree is predecessor
			if (root->left != NULL)
			{
				BTNode* tmp = root->left;
				while (tmp->right)
					tmp = tmp->right;
				pre = tmp;
			}

			// the minimum value in right subtree is successor
			if (root->right != NULL)
			{
				BTNode* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				suc = tmp;
			}
			return;
		}

		// If key is smaller than root's key, go to left subtree
		if (root->data > data)
		{
			suc = root;
			findPreSuc(root->left, pre, suc, data);
		}
		else // go to right subtree
		{
			pre = root;
			findPreSuc(root->right, pre, suc, data);
		}
	}
};