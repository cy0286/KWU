#pragma once
#include <iostream>
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <cstring>
using namespace std;

class Manager
{
private:
	ifstream	fcmd;        // Input file stream for command file
    ofstream	flog;        // Output file stream for logging
    MemberQueue memberQueue; // Instance of MemberQueue to manage a queue of members
    TermsLIST termList;       // Instance of TermsLIST to manage a list of terms
    NameBST nameBST;          // Instance of NameBST to manage a binary search tree of member names


public:
	Manager(); // Constructor
	~Manager(); //Destructor

	void run(const char* command); // Function to run the application based on a command file
	
	void PrintSuccess(const char* cmd); // Function to print a success message for a command
	void PrintErrorCode(int num); // Function to print an error code for a command

	int LOAD(); // Function to load data from a file
	int ADD(char *name, int age, char *date, char *termtype); // Function to add a new member
	int QPOP(); // Function to dequeue (pop) a member from the queue
	int SEARCH(char* name); // Function to search for a member with name
	int PRINT(char *data, ofstream* flog); // Function to print data
	int DELETE(char* data); // Function to delete a member based on data
};
