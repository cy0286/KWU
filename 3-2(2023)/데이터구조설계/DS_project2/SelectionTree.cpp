#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) 
{
    if (!newData) 
    {
        return false;
    }

    SelectionTreeNode* newNode = new SelectionTreeNode();
    newNode->setBookData(newData);

    if (!root) 
    {
        root = newNode;
    } 
    else 
    {
        SelectionTreeNode* current = root;
        SelectionTreeNode* parent = NULL;

        while (current != NULL) 
        {
            parent = current;

            // assume a comparison function for book codes, adjust as needed
            if (newData->getCode() < current->getBookData()->getCode()) 
            {
                current = current->getLeftChild();
            }
            else 
            {
                current = current->getRightChild();
            }
        }

        // set the parent of the new node
        newNode->setParent(parent);

        // attach the new node to the appropriate side of the parent
        if (newData->getCode() < parent->getBookData()->getCode()) 
        {
            parent->setLeftChild(newNode);
        } 
        else 
        {
            parent->setRightChild(newNode);
        }
    }

    return true; // successfully inserted

}

bool SelectionTree::Delete(int code) 
{
    if (!root) // the tree is empty,
    {
        return false;
    }

    SelectionTreeNode* current = root;
    SelectionTreeNode* parent = NULL;

    // search for the node to delete
    while (current != NULL && current->getBookData()->getCode() != code) 
    {
        parent = current;
        if (code < current->getBookData()->getCode()) 
        {
            current = current->getLeftChild();
        } 
        else
        {
            current = current->getRightChild();
        }
    }

    if (!current) 
    {
        // node with the specified code not found
        return false;
    }

    // Case 1: Node with no children
    if (!current->getLeftChild() && !current->getRightChild()) 
    {
        if (parent) 
        {
            // node is not the root
            if (parent->getLeftChild() == current) 
            {
                parent->setLeftChild(NULL);
            } 
            else 
            {
                parent->setRightChild(NULL);
            }
            delete current;
        } 
        else
        {
            // node is the root
            delete root;
            root = NULL;
        }
    }

    // Case 2: Node with one child
    else if (!current->getLeftChild() || !current->getRightChild()) 
    {
        SelectionTreeNode* child = (current->getLeftChild()) ? current->getLeftChild() : current->getRightChild();

        if (parent) 
        {
            // node is not the root
            if (parent->getLeftChild() == current) 
            {
                parent->setLeftChild(child);
            } 
            else 
            {
                parent->setRightChild(child);
            }
            delete current;
        } 
        else 
        {
            // node is the root
            delete root;
            root = child;
        }
    }

    // Case 3: Node with two children
    else 
    {
        SelectionTreeNode* successor = findSuccessor(current->getRightChild());
        current->setBookData(successor->getBookData());
        Delete(successor->getBookData()->getCode());
    }

    return true; // successfully deleted
}

SelectionTreeNode* SelectionTree::findSuccessor(SelectionTreeNode* node) 
{
    while (node->getLeftChild() != NULL) // iterate to the leftmost node in the right subtree
    {
        node = node->getLeftChild();
    }
    return node;
}

bool SelectionTree::printBookData(int bookCode) 
{
    SelectionTreeNode* node = findNode(root, bookCode);
    if (!node) // node not found
    { 
        return NULL;
    }
    if (node) 
    {
        LoanBookData* bookData = node->getBookData();
        cout <<  bookData->getName() << "/" << bookData->getCode() << "/" << bookData->getAuthor() << "/" << bookData->getYear() << "/" << bookData->getLoanCount() << endl;
        return true;
    }

    return false; 
}

SelectionTreeNode* SelectionTree::findNode(SelectionTreeNode* node, int bookCode)
{
    if (!node) // node not found
    { 
        return nullptr;
    }

    if (bookCode < node->getBookData()->getCode()) // if the bookCode is less than the current node's book code
    {
        return findNode(node->getLeftChild(), bookCode);
    }
    else if (bookCode > node->getBookData()->getCode()) // if the bookCode is greater than the current node's book code
    {
        return findNode(node->getRightChild(), bookCode);
    } 
    else // if the bookCode is equal to the current node's book code
    {
        return node;
    }
}