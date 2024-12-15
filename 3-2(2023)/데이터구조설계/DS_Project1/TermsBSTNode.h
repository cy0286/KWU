#pragma once
#include <iostream>
using namespace std;

class TermsBSTNode
{
private:
	string name;	   // Member's name
	int age;		   // Mamber's age
	string date_start; // Date of personal information collection
	string date_end;   // Date of membership expiration

	TermsBSTNode *left; // Pointer to the left child node
	TermsBSTNode *right; // Pointer to the right child node

public:
	TermsBSTNode() // Constructor
	{
		left = NULL;
		right = NULL;
	}
	~TermsBSTNode() // Destructor
	{

	}

	TermsBSTNode *getLeft() { return left; } // Getter method to retrieve the left child node
	TermsBSTNode *getRight() { return right; } // Getter method to retrieve the right child node

	string getName() { return name; } // Getter method to retrieve the member's name
	int getAge() { return age; } // Getter method to retrieve the member's age
	string getDate_start() { return date_start; } // Getter method to retrieve the date of membership expiration
	string getDate_end() { return date_end; } // Getter method to retrieve the membership type

	void setLeft(TermsBSTNode *left) { this->left = left; } // Setter method to set the left child node
	void setRight(TermsBSTNode *right) { this->right = right; } // Setter method to set the right child node

	void setName(string name) { this->name = name; } // Setter method to set the member's name
	void setAge(int age) { this->age = age; } // Setter method to set the member's age
	void setDate_start(string date) { this->date_start = date; } // Setter method to set the date of personal information collection
	void setDate_end(string date) { this->date_end = date; } // Setter method to set the date of membership expiration
};