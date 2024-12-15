#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) 
{
    while (pN->getParent() != NULL && pN->getBookData()->getName() < pN->getParent()->getBookData()->getName()) 
    {
        // swap the book data of the current node with its parent
        LoanBookData* tempData = pN->getBookData();
        pN->setBookData(pN->getParent()->getBookData());
        pN->getParent()->setBookData(tempData);

        pN = pN->getParent(); // move the current node pointer to its parent
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) 
{
   while (true) 
    {
        LoanBookHeapNode* minChild = NULL; 
        // check if the left child exists and its book name is less than the current node's book name
        if (pN->getLeftChild() != NULL && pN->getLeftChild()->getBookData()->getName() < pN->getBookData()->getName()) 
        {
            minChild = pN->getLeftChild();
        }
        // check if the right child exists and its book name is less than the minimum child's book name
        if (pN->getRightChild() != NULL && (minChild == NULL || pN->getRightChild()->getBookData()->getName() < minChild->getBookData()->getName())) 
        {
            minChild = pN->getRightChild();
        }
        // if a valid minimum child is found and its book name is less than the current node's book name
        if (minChild != NULL && minChild->getBookData()->getName() < pN->getBookData()->getName()) 
        {
            LoanBookData* tempData = pN->getBookData();
            pN->setBookData(minChild->getBookData());
            minChild->setBookData(tempData);

            pN = minChild;
        } 
        else // if no swapping is needed
        {
            break;
        }
    }

}

bool LoanBookHeap::Insert(LoanBookData* data) 
{
    // create a new heap node and set its book data
    LoanBookHeapNode* newNode = new LoanBookHeapNode();
    newNode->setBookData(data);

    if (root == NULL) // if the heap is empty
    {
        // the new node becomes the root
        root = newNode;
    } 
    else 
    {
        LoanBookHeapNode* parentNode = NULL;
        LoanBookHeapNode* current = root;

        while (current != NULL) // traverse the heap to find the appropriate position for the new node
        {
            parentNode = current; // store the current node as the potential parent
            // compare the book name to determine whether to move left or right in the heap
            if (data->getName() < current->getBookData()->getName()) 
            {
                current = current->getLeftChild();
            } 
            else 
            {
                current = current->getRightChild();
            }
        }
        // insert the new node as the left or right child of the parent
        if (parentNode->getLeftChild() == NULL) 
        {
            parentNode->setLeftChild(newNode);
        } 
        else 
        {
            parentNode->setRightChild(newNode);
        }

        newNode->setParent(parentNode); // set the parent of the new node 
        heapifyUp(newNode); // perform heapify-up
    }

    return true;
}