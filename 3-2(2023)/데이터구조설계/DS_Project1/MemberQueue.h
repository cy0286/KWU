#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
	int size; // Maximum size of the queue
	int frontIndex; // Start index of the queue
	int rearIndex; // End index of the queue
	MemberQueueNode *queue; // Pointer to the dynamically allocated queue array

public:
	MemberQueue(); // Constructor
	~MemberQueue(); // Destructor

	bool empty(); // Function to check if the queue is empty
	bool full(); // Function to check if the queue is full
	void push(const MemberQueueNode& member); // Function to add an element to the queue
	MemberQueueNode pop(); // Function to remove an element from the queue
	MemberQueueNode front(); // Function to return the element at the front of the queue
};
