#pragma once
#include <iostream>
using namespace std;

class MemberQueueNode
{
private:
	string name; // Member name
	int age; // Age
	string date; // Date of personal information collection
	char termtype; // Type of membership agreement

public:
	MemberQueueNode() : name(""), age(0), date(""), termtype('A') {} // Default constructor
	~MemberQueueNode() {} // Destructor

	MemberQueueNode(const string& _name, int _age, const string& _date, char _termtype) : name(_name), age(_age), date(_date), termtype(_termtype) {} // Constructor with parameters

	string getName() const { return name; } // Function to return the name
	int getAge() const { return age; } // Function to return the age
	string getDate() const { return date; } // Function to return the date of personal information collection
	char getTermtype() const { return termtype; } // Function to return the type of membership agreement
};
