#include "TermsList.h"

TermsLIST::TermsLIST() : head(nullptr) // Constructor
{
    // initializes the head pointer
}
TermsLIST::~TermsLIST() //Destructor
{
    TermsListNode *current = head;

    while (current)
    {
        TermsListNode *next = current->getNext();

        // Deallocate dynamically allocated TermsBST object
        if (current->getBSTPointer() != nullptr)
        {
            delete current->getBSTPointer();
            current->setBSTPointer(nullptr);
        }

        // Deallocate the current node
        delete current;
        current = next;
    }

    head = nullptr;
}

TermsListNode *TermsLIST::getHead() 
{
    return head; // Return a pointer to the head of the Terms List
}

void TermsLIST::insert(MemberQueueNode mnode)
{
    TermsListNode *searchnode = head; // Initialize a pointer searchnode to the head of the linked list

    if (head == NULL) // Check if the list is empty
    {
        TermsListNode *newNode = new TermsListNode(); // Create a new node 
        newNode->setTermtype(mnode.getTermtype());
        head = newNode; // Update the head to point to the new node

        TermsBST *newbst = new TermsBST();  // Create a new Binary Search Tree 
        newbst->insert(mnode);
        head->increment_member(1); // Increment the member count in the list node
        head->setBSTPointer(newbst); // Set the BST pointer in the list node
        return;
    } 

    while (searchnode->getNext() != NULL) // Traverse the list to find the appropriate node
    {
        if (searchnode->getTermtype() == mnode.getTermtype()) // If termtype matches
        {
            searchnode->getBSTPointer()->insert(mnode); // insert mnode into the BST of this node
            searchnode->increment_member(1); // Increment the member count
            return;
        }
        searchnode = searchnode->getNext();
    }

    if (searchnode->getNext() == NULL) // Until reach the end of the list
    {
        if (searchnode->getTermtype() == mnode.getTermtype()) // If the termtype mathes
        {
            searchnode->getBSTPointer()->insert(mnode); // insert mode into the BST of this node
            searchnode->increment_member(1); // Increment the member count
        }
        else
        {
            TermsListNode *newNode = new TermsListNode(); // Create a new node
            newNode->setTermtype(mnode.getTermtype()); // set termtype
            searchnode->setNext(newNode); // Attach the new node to the end of the list
            TermsBST *newbst = new TermsBST(); 
            newbst->insert(mnode); 
            newNode->increment_member(1); // Increment the member count.
            newNode->setBSTPointer(newbst); // Set the BST pointer in the new node
        }
        return;
    }
}

void TermsLIST::searchprint(char termtype, ofstream *flog)
{
    TermsListNode *current = head;
    // Traverse the linked list to find the specified termtype
    while (current)
    {
        if (current->getTermtype() == termtype) // If termtype matches
        {
            current->getBSTPointer()->print(flog);  // print the content of the associated BST
            return;
        }
        current = current->getNext();
    }
    return;
}

int TermsLIST::deletelist(char *date, char *name)
{
    TermsListNode *current = head; // Initialize a pointer current to the head of the linked list
    TermsListNode *prev = NULL; // Initialize a pointer prev to keep track of the previous node

    while (current)
    {
        int flag = current->getBSTPointer()->deletebst(date, name); // Call deletebst on the current node's BST

        if (flag)
        {
            current->decrement_member(); // Decrement the member count for the current node

            if (current->getmember() == 0)
            {
                if (prev)
                {
                    prev->setNext(current->getNext()); // Update prev to point to the next node
                }
                else
                {
                    head = current->getNext(); // Update head if the first node is being deleted
                }
                delete current; // Delete the current node
            }
            return 1; // Return 1 to indicate successful deletion
        }
        prev = current; // Update prev to the current node
        current = current->getNext(); // Move to the next node in the linked list
    }
    return 0;
}

int TermsLIST::deletelistname(char *name)
{
    TermsListNode *current = head; // Initialize a pointer current to the head of the linked list
    TermsListNode *prev = NULL;  // Initialize a pointer prev to keep track of the previous node
    int flag = 0; // Initialize a flag to track whether any deletion occurred

    while (current)
    {
        flag = 0; // Reset the flag for the current iteration

        // Call deletebstname on the current node's BST to delete entries associated with name
        current->getBSTPointer()->deletebstname(&flag, current->getBSTPointer()->getRoot(), name);

        if (flag)
        {
            current->decrement_member(); // Decrement the member count for the current node

            if (current->getmember() == 0)
            {
                if (prev)
                {
                    prev->setNext(current->getNext()); // Update prev to point to the next node
                }
                else
                {
                    head = current->getNext(); // Update head if the first node is being deleted
                }
                delete current; // Delete the current node
            }
            return 1; // Return 1 to indicate successful deletion
        }

        prev = current; // Update prev to the current node
        current = current->getNext(); // Move to the next node in the linked list
    }
    return 0;
}