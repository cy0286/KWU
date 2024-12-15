#include "BpTree.h"

int BpTree::Insert(LoanBookData* newData)
{
    if (root == NULL) // tree is empty
    {
        BpTreeDataNode* dataNode = new BpTreeDataNode();
        dataNode->insertDataMap(newData->getName(), newData);
        root = dataNode;
        return 0;
    }
    else // tree is not empty,
    {
        BpTreeNode* searchNode = searchDataNode(newData->getName()); // find the appropriate node

        if (searchNode == NULL) // search node is not found
        {
            BpTreeNode* insertLocation1 = root;
            BpTreeNode* insertLocation2 = NULL;
            map<string, LoanBookData*>* insertTemp1;
            map<string, LoanBookData*>* insertTemp2;

            while (insertLocation1->getMostLeftChild() != NULL) // traverse to the leftmost leaf node
            {
                insertLocation1 = insertLocation1->getMostLeftChild();
            }

            if (insertLocation1->getNext() != NULL) // update the insert locations
            {
                insertLocation2 = insertLocation1;
                insertLocation1 = insertLocation1->getNext();
                
            }

            while (insertLocation1 != NULL) // iterate nodes to find the appropriate insert location
            {
                if (insertLocation2 == NULL) 
                {
                    insertLocation1->insertDataMap(newData->getName(), newData); // insert the data into the node

                    if (excessDataNode(insertLocation1)) // check for excess data in the node and split if necessary
                    {
                        splitDataNode(insertLocation1);
                        return 0;
                    }
                    return 0;
                }
                else 
                {
                    map<string, LoanBookData*>::iterator it1;
                    map<string, LoanBookData*>::iterator it2;
                    insertTemp1 = insertLocation1->getDataMap();
                    insertTemp2 = insertLocation2->getDataMap();
                    
                    it1 = insertTemp1->begin();
                    it2 = insertTemp2->begin();

                    if (it2->first > newData->getName())
                    {
                        insertLocation2->insertDataMap(newData->getName(), newData);  // insert the data into the node

                        if (excessDataNode(insertLocation2))  // check for excess data in the node and split if necessary
                        {
                            splitDataNode(insertLocation2);
                            insertLocation2 = insertLocation2->getParent();

                            while (excessIndexNode(insertLocation2)) // check for excess data in the node and split if necessary
                            {
                                splitIndexNode(insertLocation2);
                                insertLocation2 = insertLocation2->getParent();
                            }
                            return 0;
                        }
                        return 0;
                    }
                    else if (it2->first < newData->getName() && it1->first > newData->getName())
                    {
                        insertLocation2->insertDataMap(newData->getName(), newData); // insert the data into the node

                        if (excessDataNode(insertLocation2)) // check for excess data in the node and split if necessary
                        {
                            splitDataNode(insertLocation2);
                            insertLocation2 = insertLocation2->getParent(); // check for excess data in the node and split if necessary

                            while (excessIndexNode(insertLocation2))
                            {
                                splitIndexNode(insertLocation2);
                                insertLocation2 = insertLocation2->getParent();
                            }
                            return 0;
                        }
                        return 0;
                    }
                }
                
                // update insert locations
                insertLocation2 = insertLocation1;
                insertLocation1 = insertLocation1->getNext();
            }
            insertLocation2->insertDataMap(newData->getName(), newData);  // insert the data into the node

            if (excessDataNode(insertLocation2)) // check for excess data in the node and split if necessary
            {
                splitDataNode(insertLocation2);
                insertLocation2 = insertLocation2->getParent();

                while (excessIndexNode(insertLocation2)) // check for excess data in the node and split if necessary
                {
                    splitIndexNode(insertLocation2);
                    insertLocation2 = insertLocation2->getParent();
                }
                return 0;
            }
            return 0;
        }
        else // if data already exists in the tree
        {
            // update the count and check for deletion conditions
            map<string, LoanBookData *> *nodemap;
            map<string, LoanBookData *>::iterator it;
            LoanBookData *patterntemp;
            nodemap = searchNode->getDataMap();
            it = (*nodemap).find(newData->getName());
            patterntemp = it->second;
            patterntemp->updateCount();

            if (patterntemp->getCode() <= 200 && patterntemp->getLoanCount() >= 3)
            {
                deleteBptree(patterntemp); // if deletion conditions are met, delete the node
                return 3;
            }
            else if (patterntemp->getCode() <= 400 && patterntemp->getLoanCount() >= 4)
            {
                deleteBptree(patterntemp); // if deletion conditions are met, delete the node
                return 3;
            }
            else if (patterntemp->getCode() <= 700 && patterntemp->getLoanCount() >= 2)
            {
                deleteBptree(patterntemp); // if deletion conditions are met, delete the node
                return 3;
            }
            return 0;
        }
    }
    return 0;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) 
{
	if (pDataNode->getDataMap()->size() > order - 1) return true; //order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) 
{
	if (pIndexNode->getIndexMap()->size() > order - 1)return true; //order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) 
{
    // create a new data node for splitting
	BpTreeNode* newdataNode = new BpTreeDataNode();
    map<string, LoanBookData*>* splitData;
    map<string, LoanBookData*>::iterator it;

    splitData = pDataNode->getDataMap();  // get the data map from the existing node
    
    // Move half of the data entries to the new data node
    for (int i = 0; i < order - (order / 2); i++)
    {
        it = --((*splitData).end());
        newdataNode->insertDataMap(it->first, it->second);
        pDataNode->deleteMap(it->first);
    }

     // adjust next and previous pointers to maintain linked list structure
    newdataNode->setNext(pDataNode->getNext());
    newdataNode->setPrev(pDataNode);
    
    if (pDataNode->getNext() != NULL)
    {
        pDataNode->getNext()->setPrev(newdataNode);
    }

    pDataNode->setNext(newdataNode);

    splitData = newdataNode->getDataMap(); // update splitData to point to the data in the new data node

    if (pDataNode->getParent() == NULL) // if the current data node is the root
    {
        // create a new index node for the root
        BpTreeNode* newIndexNode = new BpTreeIndexNode();
        it = (*splitData).begin();
        newIndexNode->insertIndexMap(it->first, newdataNode);
        newIndexNode->setMostLeftChild(pDataNode);
        newdataNode->setParent(newIndexNode);
        pDataNode->setParent(newIndexNode);
        root = newIndexNode;
    }
    else // not root
    {
        BpTreeNode* indexNode = pDataNode->getParent();
        it = (*splitData).begin();
        indexNode->insertIndexMap(it->first, newdataNode);
        newdataNode->setParent(indexNode);
    }

}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) 
{
    // create a new index node for splitting
	BpTreeNode* newindexNode = new BpTreeIndexNode();
    BpTreeNode* linkNode;
    map<string, BpTreeNode*>* splitIndex;
    map<string, BpTreeNode*>::iterator it;

    splitIndex = pIndexNode->getIndexMap(); // get the index map from the existing index node

    // move half of the index entries to the new index node
    for (int i = 0; i < order - (order / 2); i++)
    {
        it = --((*splitIndex).end());
        newindexNode->insertIndexMap(it->first, it->second);
        pIndexNode->deleteMap(it->first);
    }

    splitIndex = newindexNode->getIndexMap(); // update splitIndex to point to the index entries in the new index node

    // update parent pointers for the entries in the new index node
    for (it = (*splitIndex).begin(); it != (*splitIndex).end(); it++)
    {
        it->second->setParent(newindexNode);
    }

    // set the most left child of the new index node
    it = (*splitIndex).begin();
    newindexNode->setMostLeftChild(it->second);

    if (pIndexNode->getParent() == NULL) // if the current index node is the root
    {
        // create a new index node as the parent of the split index nodes
        BpTreeNode* newindexParent = new BpTreeIndexNode();
        newindexParent->insertIndexMap(it->first, newindexNode);
        newindexNode->deleteMap(it->first);
        newindexParent->setMostLeftChild(pIndexNode);
        newindexNode->setParent(newindexParent);
        pIndexNode->setParent(newindexParent);
        root = newindexParent;
    }
    else // not root 
    {
        BpTreeNode* indexParent = pIndexNode->getParent();
        indexParent->insertIndexMap(it->first, newindexNode);
        newindexNode->deleteMap(it->first);
        newindexNode->setParent(indexParent);
    }

}

BpTreeNode* BpTree::searchDataNode(string name) 
{
    // start the search from the root node
    BpTreeNode* pCur = root;
 	map<string, LoanBookData*>* searchMap;
    map<string, LoanBookData*>::iterator it;

    // traverse to the leftmost leaf node
    while (pCur->getMostLeftChild() != NULL)
    {
        pCur = pCur->getMostLeftChild();
    }

    while (pCur != NULL) // iterate over leaf nodes
	{
        // get the data map from the current node
        searchMap = pCur->getDataMap();
        it = searchMap->find(name);

        if (it != searchMap->end()) // check if the data is found in the current node
        {
			return pCur; // return the current node if the data is found
		}

        pCur = pCur->getNext(); // move to the next node in the linked list
    }
	return pCur;
}

bool BpTree::searchBook(string name) 
{
	BpTreeNode* pCur = root; // start the search from the root node
    
    while (pCur->getMostLeftChild() != NULL) // traverse to the leftmost leaf node
    {
        pCur = pCur->getMostLeftChild();
    }

    while (pCur != NULL) // iterate over leaf nodes
    {   
        map<string, LoanBookData*>* dataMap = pCur->getDataMap(); // get the data map from the current node

        for (auto it = dataMap->begin(); it != dataMap->end(); ++it) // iterate over the data entries in the current node
        {
            LoanBookData* bookData = it->second;
            if (bookData->getName() == name)  // check if the book name matches the target name
            {
                *fout << bookData->getName() << "/" << std::setw(3) << std::setfill('0') << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << bookData->getLoanCount() << endl;
                return true; // return true, book is found
            }
        }
        pCur = pCur->getNext(); // move to the next node in the linked list
    }

    return false; // book is not found
}

bool BpTree::searchRange(string start, string end) 
{  
    BpTreeNode* pCur = root;
    
    while (pCur->getMostLeftChild() != NULL)
    {
        pCur = pCur->getMostLeftChild();
    }

    bool found = false;

    while (pCur != NULL)
    {
        map<string, LoanBookData*>* dataMap = pCur->getDataMap();
        for (auto it = dataMap->begin(); it != dataMap->end(); ++it)
        {
            LoanBookData* bookData = it->second;
            
            string bookName = bookData->getName();
            if (bookName >= start && bookName <= end)
            {
                found = true;
                *fout << bookData->getName() << "/" << std::setw(3) << std::setfill('0') << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << bookData->getLoanCount() << endl;
                //cout << bookName << "/" << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << "/" << bookData->getLoanCount() << endl;
    
            }
            else if (bookName > end)
            {
                *fout << bookData->getName() << "/" << std::setw(3) << std::setfill('0') << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << bookData->getLoanCount() << endl;
                //cout << bookName << "/" << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << "/" << bookData->getLoanCount() << endl;
                return found;
            }
        }
        pCur = pCur->getNext();
    }

    return found;
}

int BpTree::printBptree(BpTreeNode* currentNode)
{
    if (currentNode == NULL) // if the current node is NULL
    {
        return 0;
    }

    while (currentNode->getMostLeftChild() != NULL) // traverse to the leftmost leaf node
    {
        currentNode = currentNode->getMostLeftChild();
    }

    while (currentNode != NULL) // iterate over leaf nodes
    {
        map<string, LoanBookData*>* dataMap = currentNode->getDataMap(); // get the data map from the current node
        for (auto it = dataMap->begin(); it != dataMap->end(); ++it) // iterate over the data entries in the current node
        {
            LoanBookData* bookData = it->second;
            *fout << bookData->getName() << "/" << std::setw(3) << std::setfill('0') << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << "/" << bookData->getLoanCount() << endl;
        }
        currentNode = currentNode->getNext(); // move to the next node in the linked list
    }
    return 0;
}

int BpTree::deleteBptree(LoanBookData* data)
{
    BpTreeNode *deletedatanode = getRoot(); // start the deletion from the root node
    BpTreeNode *deleteprev;

    map<string, LoanBookData *> *deletepatterns;

    if (deletedatanode == NULL) // if the root node is NULL
    {
        return 0;
    }

    while (deletedatanode->getMostLeftChild() != NULL) // traverse to the leftmost leaf node
    {
        deletedatanode = deletedatanode->getMostLeftChild();
    }

    while (deletedatanode != NULL) // iterate over leaf nodes
    {
        deleteprev = deletedatanode; // store the previous node for updating the linked list
        deletedatanode = deletedatanode->getNext(); // move to the next node in the linked list
        deletepatterns = deleteprev->getDataMap(); // get the data map from the previous node
        deletepatterns->erase(data->getName()); // erase the entry with the specified name from the data map
    }
    return 0;
}