#pragma once
#include <iostream>
using namespace std;

class NameBSTNode
{
private:
	string name;	   // Member's name
	int age;		   // Mamber's age
	string date_start; // Date of personal information collection
	string date_end;   // Date of membership expiration
	char termtype;	   // Membership type (A, B, C, D)

    NameBSTNode *left;  // Pointer to the left child node
    NameBSTNode *right; // Pointer to the right child node

public:
	NameBSTNode() // Constructor
	{
		left = NULL;
		right = NULL;
	}
	~NameBSTNode() // Destructor
	{
		
	}

	NameBSTNode *getLeft() { return left; } // Getter method to retrieve the left child node
	NameBSTNode *getRight() { return right; } // Getter method to retrieve the right child node

	string getName() { return name; } // Getter method to retrieve the member's name
	int getAge() { return age; } // Getter method to retrieve the member's age
	string getDate_start() { return date_start; } // Getter method to retrieve the date of personal information collection
	string getDate_end() { return date_end; } // Getter method to retrieve the date of membership expiration
	char getTermtype() { return termtype; } // Getter method to retrieve the membership type

	void setLeft(NameBSTNode *left) { this->left = left; } // Setter method to set the left child node
	void setRight(NameBSTNode *right) { this->right = right; } // Setter method to set the right child node

	void setName(string name) { this->name = name; } // Setter method to set the member's name
	void setAge(int age) { this->age = age; } // Setter method to set the member's age
	void setDate_start(string date) { this->date_start = date; } // Setter method to set the date of personal information collection
	void setDate_end(string date) { this->date_end = date; } // Setter method to set the date of membership expiration
	void setTermtype(char termtype) { this->termtype = termtype; } // Setter method to set the membership type
};