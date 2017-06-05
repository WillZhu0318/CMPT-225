#include "Queue.h"

using namespace std;

Queue::Queue()
{
	// set front node pointing to null
	this->front_p = nullptr;
	// set back node pointing to null
	this->back_p = nullptr;
	// set default number of element to be 0
	this->current_size = 0;
}

Queue::Queue(const Queue& q)
{
	// initialize all attributes to be 0 or nullptr
	this->current_size = 0;
	this->front_p = nullptr;
	this->back_p = nullptr;
	// use a node pointer to point the front element in the passed queue
	node* currentNodeInOtherQueue = q.front_p;
	// if the current node pointer is not nullptr, do loop
	while(currentNodeInOtherQueue != nullptr)
	{
		// enqueue the data of the current node
		this->enqueue(currentNodeInOtherQueue->data);
		currentNodeInOtherQueue = currentNodeInOtherQueue->next;
	}
}

Queue::~Queue()
{
	while(front_p != 0)
	{
		// make the temp pointer points the first element in the queue
		node* temp = front_p;
		// increment the node pointer
		front_p = front_p->next;
		// delete the temp pointer
		delete temp;
		temp = nullptr;
	}
}

void Queue::enqueue(int item)
{
	// create a new node for new data
	node* newNode = new node(item, nullptr);
	// if queue is empty
	if(current_size == 0)
	{
		// initialize front and back pointer to point at the same item
		front_p = newNode;
		back_p = newNode;
	}
	// if queue is not empty
	else
	{
		// make the new node attached to the end of queue
		back_p->next = newNode;
		// increment the back pointer by one
		back_p = back_p->next;
	}
	// increment the element number by one
	this->current_size++;
}

int Queue::dequeue()
{
	int result;
	// if queue is empty, return -1
	if(current_size == 0)
	{
		return -1;
	}
	// if queue contains only one element 
	else if(current_size == 1)
	{
		// get the data from the node
		result = front_p->data;
		// delete the pointer
		delete front_p;
		front_p = nullptr;
		// reset front and back pointer to nullptr
		front_p = nullptr;
		back_p = nullptr;
		// decrease the size
		current_size--;
	}
	// if the queue contains more than one element
	else
	{
		// get the first node in queue
		node* temp = front_p;
		// increment front pointer by one
		front_p = front_p->next;
		// get the data from the node
		result = temp->data;
		// delete the pointer
		delete temp;
		temp = nullptr;
		// decrease the size
		current_size--;
	}
	return result;
}

int Queue:: front()
{
	// if queue is empty, return -1
	if(this->current_size == 0)
		return -1;

	// if not empty, return the first element in queue
	else
		return this->front_p->data;
}

bool Queue::empty()
{
	// return true if queue is empty
	if(this->current_size == 0)
		return true;
	
	// return false if queue is not empty
	else
		return false;
}

int Queue::size()
{
	return this->current_size;
}

int Queue::makeUnique(int item)
{
	// return 0 if queue is empty
	if(current_size == 0)
	{
		return 0;
	}
	// counter to record number of instances of target item in queue
	int counter = 0;
	// node pointer used for looping through the queue
	node* currentNode = front_p;
	// if currentNode is not nullptr, looping
	while(currentNode != nullptr)
	{
		// set to true if a node is removed from queue
		bool removed = false;
		// if target item is found
		if(currentNode->data == item)
		{
			// if more than one instances are found
			if(counter > 1)
			{
				// a new node pointer to help find the previous node
				node* previousNode = front_p;
				// find the previous node of the target node
				while(previousNode->next != currentNode)
				{
					previousNode = previousNode->next;
				}
				// make the previous node point to the next node
				previousNode->next = currentNode->next;
				// use a temp pointer to hold the current node
				node* temp = currentNode;
				// increment the current node by one so it points the next element in queue
				currentNode = currentNode->next;
				// delete the found item
				delete temp;
				temp = nullptr;
				this->current_size--;
				removed = true;
			}
			// increment counter by one
			counter++;
		}
		// increment the current pointer by one if no node was removed
		if(!removed)
		{
			currentNode = currentNode->next;
		}
	}
	// if items are deleted from queue, update the back_p
	// there might be a chance that back_p was removed from queue
	if(counter > 1)
	{
		back_p = front_p;
		// if back_p is not the last element, increment by one
		while(back_p->next != nullptr)
		{
			back_p = back_p->next;
		}
	}
	return counter-1;
}