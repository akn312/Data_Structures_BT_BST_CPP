#include "NodeTypes.h"
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

//Creates in a node in the binary tree.
//The code is almost similar to what was covered in the labs.
class BinaryTree
{
	BTNode* ccreateBTNode(BTNode* parent, string data)
	{
		// If BinaryTree doesn't exist
		// create a new node as root
		// or it's reached when
		// there's no any child node
		// so we can insert a new node here
		if (parent == NULL)
		{
			parent = new BTNode;
			parent->data = data;
			parent->left = NULL;
			parent->right = NULL;
			parent->parent = NULL;
			return parent;
		}
		// If the left node is empty
		// then create node in left
		else if (parent->left == NULL) {
			parent->left = ccreateBTNode(parent->left, data);
			parent->right->parent = parent;
			return parent->left;
		}
		// If the right node is empty
		// then create node in right
		else
		{
			parent->right = ccreateBTNode(parent->right, data);
			parent->left->parent = parent;
			return parent->right;
		}

	}

	//Returns the height of the binary tree. 
	//The height of the tree is the longest path from the root node to any leaf node in the tree
	public: static int height(BTNode* root)
	{
		if (root == NULL)
			return -1;
		else
		{
			/* compute the depth of each subtree */
			int lDepth = height(root->left);
			int rDepth = height(root->right);

			/* use the larger one */
			if (lDepth > rDepth)
				return(lDepth + 1);
			else return(rDepth + 1);
		}
	}

	//Returns true if the binary tree is empty and false, otherwise.
	//if a tree is empty then there are no elements in it and the parent is null.
	bool isEmptyTree(BTNode* root)
	{
		if (root->parent == NULL)
			return true;
		else
			return false;
	}

	//Returns true if the two binary trees supplied as parameters are identical.
	//Two binary trees are identical if they contain the same values in exactly the same positions in each tree.
	public: static bool isEqual(BTNode* root1, BTNode* root2)
	{
	// Check if both the trees are empty
		if (root1 == NULL && root2 == NULL)
			return true;
		// If any one of the tree is non-empty
		// and other is empty, return false
		else if (root1 != NULL && root2 == NULL)
			return false;
		else if (root1 == NULL && root2 != NULL)
			return false;
		else { // Check if current data of both trees equal
			// and recursively check for left and right subtrees
			if (root1->data == root2->data && isEqual(root1->left, root2->left)
				&& isEqual(root1->right, root2->right))
				return true;
			else
				return false;
		}
	}	

	//Outputs the pre - order traversal of the binary tree.The code must be non - recursive.
	public : static string* preOrder(BTNode* root)
	{
		if (root == NULL)
			return NULL;

		stack<BTNode*> st;
		string* names = new string();

		// start from root node (set current node to root node)
		BTNode* curr = root;

		// run till stack is not empty or current is not NULL		
		while (!st.empty() || curr != NULL) {
			// Print left children while exist
			// and keep pushing right into the
			// stack.
			while (curr != NULL) {
				//cout << curr->data << " ";
				names->append(curr->data);
				names->append(" ");
				if (curr->right)
					st.push(curr->right);

				curr = curr->left;
			}			
			// when curr is NULL,
			// take out a right child from stack
			if (st.empty() == false) {
				curr = st.top();
				st.pop();
			}
		}
		return names;
	}
	//Returns the weight of the binary tree.
	//The weight of a binary tree is the amount of leaves in the tree.
	public: static int weight(BTNode* root)
	{
		if (root == NULL)
			return 0;
		if (root->left == NULL && root->right == NULL)
			return 1;
		else
			return weight(root->left) +
			weight(root->right);
	}

	//gets width at each level : The width of a binary tree is the number of nodes at any level of the tree.
	public : static int getWidth(BTNode* root, int level)
	{
		if (root == NULL)
			return 0;

		if (level == 1)
			return 1;

		else if (level > 1)
			return getWidth(root->left, level - 1)
			+ getWidth(root->right, level - 1);
	}

	//Returns the width of the binary tree.The width of a binary tree is the maximum number of nodes at any level of the tree.
	//The Programming Guidelines section explains how to find the amount of nodes in a given level.
	public: static int width(BTNode* root)
	{
		int maxWidth = 0;
		int width;
		int h = height(root);
		int i;

		//Get width of each level and compare the width with maximum width so far
		for (i = 1; i <= h; i++) {
			width = getWidth(root, i);
			if (width > maxWidth)
			{
				maxWidth = width;
			}
		}
		return maxWidth;
	}
};



