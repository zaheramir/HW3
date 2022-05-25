#ifndef EX3_Queue_H
#define EX3_Queue_H

#include <iostream>


template<class T>
class Queue
{
public:
	class Iterator;
	Iterator begin() const
	{
		return Iterator(this, 0);
	}

	Iterator end() const
	{
		return Iterator(this, size());
	}

	Queue()
	{
		this->head = new Node();
		this->head->next = nullptr;
		this->rear = nullptr;
		this->current = this->head;
	}

	~Queue()
	{
		delete this->head;
		delete this->rear;
	}

	void pushBack(T object)
	{
		Node* newNode = new Node();

		newNode->data = object;
		newNode->next = nullptr;

		if (this->rear == nullptr)
		{
			this->head->next = newNode;
			this->rear = newNode;
		}
		else
		{
			this->rear->next = newNode;
			this->rear = this->rear->next;
			this->rear->next = nullptr;
		}
	}

	void popFront()
	{
		if (this->head->next != nullptr)
		{
			Node* toDelete = this->head->next;
			this->head->next = this->head->next->next;
			delete toDelete;
		}
	}

	T& front()
	{
		if (this->size() == 0)
		{
			throw EmptyQueue();
		}
		return this->head->next->data;
	}
	
	int size() const
	{
		int queueSize = 0;
		Node* current = head->next;

		while (current != nullptr)
		{
			current = current->next;
			queueSize++;
		}

		return queueSize;
	}
	
	class EmptyQueue{};

private:

	struct Node
	{
		T data;
		Node* next;
	};

	Node* head;
	Node* rear;
	Node* current;
	T arr[];
	
};

template<class T>
class Queue<T>::Iterator {
public:
	const T& operator*() const
	{
		Node* current = queue->head->next;
		
		for (int i = 0; current->next != nullptr; i++)
		{
			if (index == i)
			{
				return current->data;
			}
			current = current->next;
		}
	}

	Iterator& operator++()
	{
		/*if (this->queue->end() == *this)
		{
			throw InvalidOperation();
		}*/

		++index;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator result = *this;
		++*this;
		return result;
	}

	bool operator==(const Iterator& it) const
	{
		if (queue == it.queue)
		{
			return index == it.index;
		}

		return false;
	}
	class InvalidOperation{};

	bool operator!=(const Iterator& it) const
	{
		bool ans = !(*this == it);
		return ans;
	}

	Iterator(const Iterator&) = default;
	Iterator& operator=(const Iterator&) = default;

private:
	const Queue<T>* queue;
	int index;
	Iterator(const Queue<T>* queue, int index) : queue(queue), index(index)
	{}
	friend class Queue<T>;

};





#endif //EX3_Queue_H

template<class T, class Condition>
Queue<T> filter(Queue<T>& queueToFilter, Condition c)
{
	Queue<T> tempQueue = new Queue<T>;
	for (int i = 0; i < queueToFilter.size(); i++)
	{
		tempQueue.pushBack(queueToFilter.front());
	}
	tempQueue = queueToFilter;
	Queue<T> filteredQueue;
	for (int i = 0; i < tempQueue.size(); i++)
	{
		if (c(tempQueue.front()))
		{
			filteredQueue.pushBack(tempQueue.front());
		}
		tempQueue.popFront();
	}

	delete tempQueue;
	return filteredQueue;
}
