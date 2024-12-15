#include "NameBST.h"

NameBST::NameBST() : root(nullptr) // Constructor
{
    // Initializes root to nullptr
}

NameBST::~NameBST() // Destructor
{

}

NameBSTNode *NameBST::getRoot()
{
    return root;
}

void NameBST::setRoot(NameBSTNode *node)
{
    this->root = node;
}

void NameBST::insert(MemberQueueNode data)
{
    // Create a temporary character array temp and parse the date from data
    char temp[100];
    strcpy(temp, data.getDate().c_str());
    int year = stoi(strtok(temp, "-"));
    int month = stoi(strtok(NULL, "-"));
    int date = stoi(strtok(NULL, "-"));

    // Get the term type and calculate the expiration date in months
    char termType = data.getTermtype();
    int expiration_date = 0;

    switch (termType)
    {
    case 'A':
        expiration_date = 6;
        break;
    case 'B':
        expiration_date = 12;
        break;
    case 'C':
        expiration_date = 24;
        break;
    case 'D':
        expiration_date = 36;
        break;
    default:
        break;
    }

    // Calculate the new expiration date in terms of years and months
    if(expiration_date == 6)
    {
        year += (expiration_date + month) / 13;
        month = (expiration_date + month) % 12;
        if(month == 0){month = 12;}
    }
    else if(expiration_date == 12)
    {
        year += 1;
    }
    else if(expiration_date == 24)
    {
        year += 2;
    }
    else
    {
        year += 3;
    }

    // Create a new character array temp2 to format the new expiration date
    char temp2[100] = {0};
    strcat(temp2, to_string(year).c_str());
    strcat(temp2, "-");
    if (month < 10)
    {
        strcat(temp2, "0");
    }
    strcat(temp2, to_string(month).c_str());
    strcat(temp2, "-");
    if (date < 10)
    {
        strcat(temp2, "0");
    }
    strcat(temp2, to_string(date).c_str());

    NameBSTNode *newnode = new NameBSTNode();
    newnode->setName(data.getName());
    newnode->setAge(data.getAge());
    newnode->setDate_start(data.getDate());
    newnode->setDate_end(temp2);

    if (root == NULL) // Check if the binary search tree is empty
    {
        root = newnode;  // set the new node as the root
    }
    else
    {
        NameBSTNode *tempnode = root;

        // Traverse the tree to find the appropriate location for insertion
        while (tempnode != NULL)
        {
            int compareResult = strcmp(data.getName().c_str(), tempnode->getName().c_str());

            if (compareResult <= 0)
            {
                if (tempnode->getLeft() == NULL)
                {
                    tempnode->setLeft(newnode); // Insert as the left child if available
                    break;
                }
                else
                {
                    tempnode = tempnode->getLeft(); // Move to the left subtree
                }
            }
            else
            {
                if (tempnode->getRight() == NULL)
                {
                    tempnode->setRight(newnode); // Insert as the right child if available
                    break;
                }
                else
                {
                    tempnode = tempnode->getRight(); // Move to the right subtree
                }
            }
        }
    }
}

void NameBST::searchRecursive(NameBSTNode *currentNode, char *data, ofstream *log)
{
    if (currentNode == NULL) // If the current node is NULL
    {
        return;
    }

    searchRecursive(currentNode->getLeft(), data, log); // Recursively search the left subtree
    
    if (strcmp(data, currentNode->getName().c_str()) == 0) // Check if the data matches the name of the current node
    {
        *log << currentNode->getName() << "/" << currentNode->getAge() << "/" << currentNode->getDate_start() << "/" << currentNode->getDate_end() << endl;
        searchflag++; // Increment the search flag to count the number of matches found
    }
    searchRecursive(currentNode->getRight(), data, log); // Recursively search the right subtree
}

int NameBST::search(char *data, ofstream *log)
{
    searchflag = 0; // Reset the search flag to 0
    searchRecursive(root, data, log); // Start the search from the root node
    return searchflag;// Return the count of matches found
} 

void NameBST::inorderPrint(NameBSTNode *node)
{
    if (node == NULL) // If the current node is NULL
    {
        return;
    }

    inorderPrint(node->getLeft()); // Recursively traverse the left subtree

    *flog << node->getName() << "/" << node->getAge() << "/" << node->getDate_start() << "/" << node->getDate_end() << endl;

    inorderPrint(node->getRight()); // Recursively traverse the right subtree
}

void NameBST::print(ofstream *log)
{
    flog = log; // Store the log file in flog
    inorderPrint(root); // Start the inorder traversal from the root node
}

NameBSTNode* NameBST::deletename(int copy,NameBSTNode* node, char *end_date, const char *name)
{
    if (node == NULL) // If the node is NULL
    {
        return node; // return it
    }
    
    // Process of finding the node to delete
    int compareResult = strcmp(name, node->getName().c_str());
    
    if (compareResult < 0) // If name is smaller
    {
        node->setLeft(deletename(copy, node->getLeft(), end_date, name)); // move to the left subtree
    }
    else if (compareResult > 0) // If name is larger
    {
        node->setRight(deletename(copy, node->getRight(), end_date, name)); // move to the right subtree
    }
    else
    {
        // If the node to delete is found

        // 1. Case where the node has no children or only one child
        if (node->getLeft() == NULL) // Check if the left child of the current node is NULL
        {
            if(copy == 0) // copy end_date from the current node
            {
                strcpy(end_date, node->getDate_end().c_str());
            }
            NameBSTNode *temp = node->getRight(); // set it to the right child of the current node
            
            delete node; // Delete the current node from the memory
            return temp; // Return temp as the new node to replace the deleted node
        }
        else if (node->getRight() == NULL) // Check if the right child of the current node is NULL
        {
            if(copy == 0) // copy end_date from the current node
            {
                strcpy(end_date, node->getDate_end().c_str()); 
            }
            NameBSTNode *temp = node->getLeft(); // set it to the left child of the current node
    
            delete node; // Delete the current node from the memory
            return temp; // Return temp as the new node to replace the deleted node
        }

       // 2. Case where the node has two children
        NameBSTNode *minValueNode = findMinValueNode(node->getRight());
        
        strcpy(end_date, node->getDate_end().c_str()); // Copy the end_date value from the current node to the end_date parameter
        copy++;

        // Update various properties of the current node
        node->setName(minValueNode->getName());
        node->setAge(minValueNode->getAge());
        node->setDate_start(minValueNode->getDate_start());
        node->setDate_end(minValueNode->getDate_end());
        node->setTermtype(minValueNode->getTermtype());

        // Recursively call deletename on the right child of the current node to delete the minValueNode
        node->setRight(deletename(copy, node->getRight(), end_date, minValueNode->getName().c_str()));
    }
    return node; // Return the updated node after performing the necessary updates and deletions
}

NameBSTNode* NameBST::findMinValueNode(NameBSTNode *node)
{
    while (node->getLeft() != NULL) // Start a loop while the left child of the current node is not NULL
    {
        node = node->getLeft(); // Move to the left child of the current node
    }
    return node; // Return the node with the minimum value found by traversing the leftmost path in the tree
}