#include "TermsBST.h"

TermsBST::TermsBST() // Constructor
{

}
TermsBST::~TermsBST() // Destructor
{

}

TermsBSTNode *TermsBST::getRoot()
{
	return root;
}

void TermsBST::setRoot(TermsBSTNode *node)
{
	this->root = node;
}

void TermsBST::insert(MemberQueueNode data)
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
    char temp2[100] = { 0 };
    
	strcat(temp2, to_string(year).c_str());
	strcat(temp2, "-");
	if(month < 10)
	{
		strcat(temp2, "0");
	}
	strcat(temp2, to_string(month).c_str());
	strcat(temp2, "-");
	if(date < 10)
	{
		strcat(temp2, "0");
	}
	strcat(temp2, to_string(date).c_str());

    TermsBSTNode* newnode = new TermsBSTNode();
    newnode->setName(data.getName());
    newnode->setAge(data.getAge());
    newnode->setDate_start(data.getDate());
    newnode->setDate_end(temp2);

    if (root == NULL) // Check if the binary search tree is empty
    {
        root = newnode; // set the new node as the root 
    }
    else
    {
        insertNode(root, newnode); // insert the new node starting from the root
    }
}

void TermsBST::insertNode(TermsBSTNode* currentNode, TermsBSTNode* newNode)
{
    int compareResult = strcmp(currentNode->getDate_end().c_str(), newNode->getDate_end().c_str());

    if (compareResult <= 0)
    {
        if (currentNode->getRight() == NULL)
        {
            currentNode->setRight(newNode); // Insert as the left child if available
        }
        else
        {
            insertNode(currentNode->getRight(), newNode); // Move to the left subtree
        }
    }
    else
    {
        if (currentNode->getLeft() == NULL)
        {
            currentNode->setLeft(newNode); // Insert as the right child if available
        }
        else
        {
            insertNode(currentNode->getLeft(), newNode); // Move to the right subtree
        }
    }
}

void TermsBST::inorderPrint(TermsBSTNode *node)
{
	if (node == NULL) // If the current node is NULL
	{
		return;
	}

	inorderPrint(node->getLeft()); // Recursively traverse the left subtree

	*flog << node->getName() << "/" << node->getAge() << "/" << node->getDate_start() << "/" << node->getDate_end() << endl;

	inorderPrint(node->getRight()); // Recursively traverse the right subtree
}

void TermsBST::print(ofstream *log)
{
	flog = log; // Store the log file in flog
	inorderPrint(root); // Start the inorder traversal from the root node
}

int TermsBST::deletebst(char* end_date, char* name)
{
    // Initialize current and prev pointers to the root of the binary search tree
    TermsBSTNode* current = root;
    TermsBSTNode* prev = root;

    // Traverse the binary search tree to find the leftmost node (minimum value node)
    while(current->getLeft() != NULL)
    {
        prev = current;
        current = current->getLeft();
    }

    // Check if the end_date of the leftmost node is less than end_date provided
    if (strcmp(current->getDate_end().c_str(), end_date) < 0)
    {
        if(current == root) // If the leftmost node is the root node
        {
            root = current->getRight(); // Update the root to the right child of the leftmost node
            strcpy(name, current->getName().c_str()); // Copy the name of the deleted node
            delete current; // Delete the leftmost node
            return 1; // Return 1 to indicate successful deletion
        }
        if(current->getRight() == NULL) // If the leftmost node has no right child
        {
            strcpy(name, current->getName().c_str()); // Copy the name of the deleted node
            delete current;  // Delete the leftmost node
            prev->setLeft(NULL); // Set the left child of prev to NULL
            return 1; // Return 1 to indicate successful deletion
        }
        else
        {
            prev->setLeft(current->getRight()); // Update the left child of prev to the right child of the leftmost node
            strcpy(name, current->getName().c_str()); // Copy the name of the deleted node
            delete current; // Delete the leftmost node
            return 1; // Return 1 to indicate successful deletion
        }       
    }
    return 0; // Return 0 to indicate no node was deleted
}

TermsBSTNode* TermsBST::deletebstname(int* flag, TermsBSTNode* node, const char* name)
{
    if (node == NULL)
    {
        return node;
    }

    int compareResult = strcmp(name, node->getName().c_str());
    
    if (compareResult < 0) // If name is smaller
    {
        node->setLeft(deletebstname(flag, node->getLeft(), name)); // move to the left subtree
    }
    else if (compareResult > 0) // If name is larger
    {
        node->setRight(deletebstname(flag, node->getRight(), name)); // move to the right subtree
    }
    else
    {
        *flag = 1;
        // If the node to delete is found

        // 1. Case where the node has no children or only one child
        if (node->getLeft() == NULL)
        {
            TermsBSTNode *temp = node->getRight(); // set it to the right child of the current node
            
            delete node; // Delete the current node from the memory
            return temp; // Return temp as the new node to replace the deleted node
        }
        else if (node->getRight() == NULL)
        {
            TermsBSTNode *temp = node->getLeft(); // set it to the left child of the current node
    
            delete node; // Delete the current node from the memory
            return temp; // Return temp as the new node to replace the deleted node
        }

        // 2. Case where the node has two children
        TermsBSTNode *minValueNode = findMinValueNode(node->getRight());

        // Update various properties of the current node
        node->setName(minValueNode->getName());
        node->setAge(minValueNode->getAge());
        node->setDate_start(minValueNode->getDate_start());
        node->setDate_end(minValueNode->getDate_end());

        // Recursively call deletename on the right child of the current node to delete the minValueNode
        node->setRight(deletebstname(flag, node->getRight(), minValueNode->getName().c_str())); // Copy the end_date value from the current node to the end_date parameter
    }
    return node; // Return the updated node after performing the necessary updates and deletions
}

TermsBSTNode* TermsBST::findMinValueNode(TermsBSTNode *node)
{
    while (node->getLeft() != NULL) // Start a loop while the left child of the current node is not NULL
    {
        node = node->getLeft(); // Move to the left child of the current node
    }
    return node; // Return the node with the minimum value found by traversing the leftmost path in the tree
}