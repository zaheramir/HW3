#ifndef EX3_Queue_H
#define EX3_Queue_H

#define DEFAULT_SIZE 2

template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue&);
	~Queue();
	
	void pushBack(T value);
	T& front();
	void popFront();
	int size() const;

	class Iterator;
	Iterator begin() const
	{
		return Iterator(this, 0);
	}
	
	Iterator end() const
	{
		return Iterator(this, size());
	}

private:
	T* arr;
	int frontIndex;
	int rearIndex; //also represents the size of the array
	int maxQueueSize;
	T value;
	void expand();
};

template<class T>
class Queue<T>::Iterator {
public:
	const T& operator*() const
	{
		return this->queue->arr[this->index];
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

template<class T>
int Queue<T>::size() const
{
	int queueSize = rearIndex + 1;
	return queueSize;
}

template<class T>
Queue<T>::Queue()
{
	this->arr = new T[DEFAULT_SIZE];
	this->frontIndex = 0;
	this->rearIndex = -1;
	this->maxQueueSize = DEFAULT_SIZE;
}

template<class T>
Queue<T>::Queue<T>(const Queue<T>& queue) : arr(new T[queue.maxQueueSize])
{
	this->frontIndex = queue.frontIndex;
	this->rearIndex = queue.rearIndex;
	this->maxQueueSize = queue.maxQueueSize;

	for (int i = 0; i < (this->rearIndex + 1); i++)
	{
		this->arr[i] = queue.arr[i];
	}
}

template<class T>
Queue<T>::~Queue()
{
	delete[] this->arr;
}

template<class T>
void Queue<T>::expand()
{
	T newSize = (rearIndex + 1) + DEFAULT_SIZE;
	T* newData = new T[newSize];

	for (int i = 0; i < this->rearIndex + 1; ++i) {
		newData[i] = arr[i];
	}

	delete[] arr;
	arr = newData;
	maxQueueSize = newSize;
}

template<class T>
void Queue<T>::pushBack(T value)
{
	this->rearIndex++;
	if (this->rearIndex >= this->maxQueueSize)
	{
		expand();
	}
	this->arr[this->rearIndex] = value;
}

template<class T>
T& Queue<T>::front()
{
	return this->arr[0];
}

template<class T>
void Queue<T>::popFront()
{
	int queueSize = rearIndex + 1;
	if (queueSize <= 0)
	{
		throw;
	}

	T* newData = new T[queueSize];

	for (int i = 1 ; i < queueSize; ++i) {
		newData[i - 1] = arr[i];
	}

	delete[] arr;
	this->rearIndex--;
	arr = newData;
	
}

template<class T, class Condition>
Queue<T> filter(Queue<T>& queueToFilter, Condition c)
{
	Queue<T> tempQueue = queueToFilter;
	Queue<T> filteredQueue;

	for (int i = 0; i < queueToFilter.size(); i++)
	{
		if (c(tempQueue.front()))
		{
			filteredQueue.pushBack(tempQueue.front());
		}
		tempQueue.popFront();
	}
	
	return filteredQueue;
}

#endif //EX3_Queue_H

