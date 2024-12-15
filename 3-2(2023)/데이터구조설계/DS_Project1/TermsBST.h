#pragma once
#include "TermsBSTNode.h"
#include "MemberQueueNode.h"
#include <cstring>
#include <fstream>

class TermsBST
{
private:
	TermsBSTNode *root = NULL; // The root of the binary search tree
	ofstream *flog; // The output file stream for logging

public:
	TermsBST(); // Constructor
	~TermsBST(); // Destructor

	TermsBSTNode *getRoot(); // Getter method to retrieve the root node of the binary search tree
	void setRoot(TermsBSTNode *node); // Setter method to set the root node of the binary search tree

	void insert(MemberQueueNode data); // Function to insert a new node into the binary search tree based on data
	void insertNode(TermsBSTNode *currentNode, TermsBSTNode *newNode); // Function to insert a new newNode into the binary search tree starting from currentNode
	void print(ofstream *log); // Function to print the binary search tree in an inorder traversal to a log file
	void inorderPrint(TermsBSTNode *node); // Function for recursive inorder traversal and printing nodes
	int deletebst(char* end_date, char* name); // Function to delete a node with name and end_date in the binary search tree
	TermsBSTNode* deletebstname(int* flag, TermsBSTNode* node, const char* name); // Recursive function to delete a node with name and update the flag
	TermsBSTNode* findMinValueNode(TermsBSTNode *node); // Function to find the node with the minimum value in a binary search tree
};