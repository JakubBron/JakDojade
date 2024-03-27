#pragma once

#define QUEUE_EMPTY -10

template<typename T>
class Queue {
private:
	struct Node{
		T value;
		Node* next;
	};

	Node* frontNode = nullptr;
	Node* endNode = nullptr;
	int size = 0;

public:
	void push(T value);
	void pop();
	T& front();
	bool empty();
	~Queue();
};

template<typename T>
void Queue<T>::push(T value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = nullptr;

	if (frontNode == nullptr)
	{
		frontNode = newNode;
	}
	else 
	{
		endNode->next = newNode;
	}

	endNode = newNode;
	size++;
}

template<typename T>
void Queue<T>::pop() {
	
	if (frontNode == nullptr)
	{
		throw QUEUE_EMPTY;
	}
	Node* temp = frontNode;
	frontNode = frontNode->next;
	size--;
	delete temp;
}


template<typename T>
T& Queue<T>::front() {
	
	if (frontNode == nullptr) 
	{
		throw QUEUE_EMPTY;
	}

	return frontNode->value;
}

template<typename T>
bool Queue<T>::empty() {
	return (size <= 0);
}

template<typename T>
Queue<T>::~Queue() {
	while (!empty())
	{
		pop();
	}
}