#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
    size = 100; // Set the maximum size of the queue to 100
    frontIndex = -1; // Initialize the start index of the queue
    rearIndex = -1;  // Initialize the end index of the queue
    queue = new MemberQueueNode[size]; // Create a dynamic array for the queue
}

MemberQueue::~MemberQueue()
{
    delete[] queue; // Free the memory allocated for the dynamic queue array
}

bool MemberQueue::empty()
{
    bool isEmpty = (frontIndex == -1); // Check if the queue is empty
    if (isEmpty) // If the queue is empty
    {
        cout << "Queue is empty." << endl; 
    }
    return isEmpty;
}

bool MemberQueue::full()
{
    bool isFull = (rearIndex + 1) % size == frontIndex; // Check if the queue is completely filled
    if (isFull) // If the queue is full
    {
        cout << "Queue is full." << endl;  
    }
    return isFull;
}

void MemberQueue::push(const MemberQueueNode &member)
{
    if (!full()) // If the queue is not completely filled
    {
        if (frontIndex == -1)
        {
            frontIndex = 0; // Initialize the frontIndex
        }
        rearIndex = (rearIndex + 1) % size; // Update the end index of the queue
        queue[rearIndex] = member; // Add an element to the queue
    }
    else // If the queue is full
    {
        cout << "Queue is full." << endl;
    }
}

MemberQueueNode MemberQueue::pop()
{
    if (!empty()) // If the queue is not empty
    {
        MemberQueueNode member = queue[frontIndex]; // Get the front element of the queue

        if (frontIndex == rearIndex)
        {
            frontIndex = -1; // Indicate that the queue is empty
            rearIndex = -1;  // Indicate that the queue is empty
        }
        else
        {
            frontIndex = (frontIndex + 1) % size; // Update frontIndex to remove an element
        }
        return member; // Return the removed element
    }
    else // If the queue is empty
    {
        cout << "Queue is empty." << endl;
        return MemberQueueNode(); // Return the default value
    }
}

MemberQueueNode MemberQueue::front()
{
    if (!empty()) // If the queue is not empty
    {
        return queue[frontIndex]; // Return the front element of the queue
    }
    else // If the queue is empty 
    {
        cout << "Queue is empty." << endl;
        return MemberQueueNode(); // Return the default value
    }
}