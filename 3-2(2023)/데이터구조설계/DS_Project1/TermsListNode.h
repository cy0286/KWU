#pragma once
#include <iostream>
#include "TermsBST.h"
using namespace std;

class TermsListNode
{
private:
	TermsListNode* next = NULL; // Pointer to the next TermsListNode
   char termtype; // Type of membership agreement
    int numMember = 0; // Number of members associated with this agreement type
    TermsBST* bstPointer = NULL; // Pointer to the BST containing members for this agreement type

public:
	TermsListNode() {} // Default constructor
    ~TermsListNode()
    {
        if (bstPointer != NULL)
        {
            delete bstPointer; // Delete the associated BST to free memory
            bstPointer = NULL; // Set the pointer to NULL after deletion
        }
    }
	TermsListNode *getNext() { return next; } // Retrieve the pointer to the next node in the list
    TermsBST* getBSTPointer() { return bstPointer; } // Retrieve the BST pointer

	void setNext(TermsListNode *next) { this->next = next; } // Set the pointer to the next node in the list
    void setTermtype(char termtype) { this->termtype = termtype; } // Set the type of membership agreement
    void setBSTPointer(TermsBST* bstnode) { this->bstPointer = bstnode; } // Set the BST pointer
    char getTermtype() const { return termtype; } // Get the type of membership agreement
    int getmember() const { return numMember; } // Get the number of members associated with this agreement type
    void increment_member(int num) { numMember += num; } // Increment the member count by a specified number
    void decrement_member() { numMember--; } // Decrement the member count
};