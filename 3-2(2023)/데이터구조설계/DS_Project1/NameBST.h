#pragma once
#include "NameBSTNode.h"
#include "MemberQueueNode.h"
#include <cstring>
#include <fstream>

class NameBST
{
private:
	NameBSTNode* root = NULL; // The root of the binary search tree
    ofstream* flog; // The output file stream for logging
    int searchflag = 0; // To count search results

public:
	NameBST(); // Constructor
	~NameBST(); // Destructor

	NameBSTNode* getRoot(); // Getter method to retrieve the root node of the binary search tree
    void setRoot(NameBSTNode *node); // Setter method to set the root node of the binary search tree

    void insert(MemberQueueNode data); // Function to insert a new member into the binary search tree
    int search(char* data, ofstream* log); // Function to search for a specific data in the binary search tree and return the count of matches
    void searchRecursive(NameBSTNode* currentNode, char* data, ofstream* log); // Recursive function to search for data within the binary search tree
	void print(ofstream* log); // Function to print the binary search tree in an inorder traversal to a log file
	void inorderPrint(NameBSTNode *node); // Recursive function for inorder traversal and printing nodes
	NameBSTNode* deletename(int copy, NameBSTNode* node, char* end_date, const char* name); // Function to delete a node with a given name in the binary search tree
	NameBSTNode* findMinValueNode(NameBSTNode *node); // Function to find the node with the minimum value in a binary search tree
};