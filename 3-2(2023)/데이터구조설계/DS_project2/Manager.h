#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	char cmd[100];
	BpTree* bptree;
	SelectionTree* stree;
	LoanBookHeap* heap;
public:
	Manager(int bpOrder)	//constructor
	{
		bptree = new BpTree(&flog, bpOrder);
		stree = new SelectionTree(&flog);
		heap = new LoanBookHeap();
	}


	~Manager()//destructor
	{
		/* You must fill here */
	}

	ifstream fin;
	ifstream datafile;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool ADD(LoanBookData *temp);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(LoanBookData *temp);

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode();

};

