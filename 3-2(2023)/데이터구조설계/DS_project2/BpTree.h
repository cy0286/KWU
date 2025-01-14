#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>

class BpTree 
{
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order = 3) 
	{
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {};
	
	/* essential */
	int		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* setRoot(BpTreeNode* newRoot) { return newRoot; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	//LoanBookData* searchBook(string name);
	bool searchRange(string start, string end);
	
	int printBptree(BpTreeNode* currentNode);
	int deleteBptree(LoanBookData* data);

};

#endif
