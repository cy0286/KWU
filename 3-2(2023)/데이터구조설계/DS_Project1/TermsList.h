#pragma once
#include "TermsListNode.h"
#include "TermsBST.h"
#include "MemberQueueNode.h"

class TermsLIST
{
private:
	TermsListNode* head = NULL; // Pointer to the head of the Terms List, initially set to NULL

public:
	TermsLIST(); // Constructor
	~TermsLIST(); // Destructor

	TermsListNode* getHead(); // Retrieve the pointer to the head of the Terms List

	void insert(MemberQueueNode mnode);  // Function to insert a MemberQueueNode into the Terms List
	void searchprint(char termtype, ofstream *flog);  // Function to search for and print members of a specific term type
	int deletelist(char* date, char* name); // Function to delete a list of members based on date and name
	int deletelistname(char *name); // Function to delete a list of members with a specific name
};
