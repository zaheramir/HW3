#ifndef EX3_Queue_H
#define EX3_Queue_H

#define DEFAULT_SIZE 50

template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();
	
	void pushBack(T value);
	T& front() const;
	void popFront();
	int size() const;

	class Iterator;
	class ConstIterator;
	
	Iterator begin() 
	{
		return Iterator(this, 0);
	}
	
	Iterator end() 
	{
		return Iterator(this, size());
	}

	ConstIterator begin() const
	{
		return ConstIterator(this, 0);
	}

	ConstIterator end() const
	{
		return ConstIterator(this, size());
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
	Iterator(const Iterator&) = default;
	Iterator& operator=(const Iterator&) = default;

	const T& operator*() const;
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator & it) const;
	bool operator!=(const Iterator & it) const;

	class InvalidOperation {};

private:
	const Queue<T>* queue;
	int index;
	Iterator(const Queue<T>* queue, int index) : queue(queue), index(index)
	{}
	friend class Queue<T>;

};

template<class T>
class Queue<T>::ConstIterator {
public:
	ConstIterator(const ConstIterator&) = default;
	ConstIterator& operator=(const ConstIterator&) = default;

	const T& operator*() const;
	ConstIterator& operator++();
	ConstIterator operator++(int);
	bool operator==(const ConstIterator& it) const;
	bool operator!=(const ConstIterator& it) const;

	class InvalidOperation {};
private:
	const Queue<T>* queue;
	int index;
	ConstIterator(const Queue<T>* queue, int index) : queue(queue), index(index)
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
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
	if (this == &queue)
	{
		return *this;
	}

	delete[] this->arr;
	arr = new int[queue.maxQueueSize];
	maxQueueSize = queue.maxQueueSize;
	rearIndex = queue.rearIndex;

	for (int i = 0; i <= rearIndex; i++)
	{
		arr[i] = queue.arr[i];
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
T& Queue<T>::front() const
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

template<class T, class Alter>
void transform(Queue<T>& queueToTransform, Alter a)
{
	Queue<T> transformedQueue;
	for (int i = 0; i < queueToTransform.size(); i++)
	{
		a(queueToTransform.front());
		transformedQueue.pushBack(queueToTransform.front());
		queueToTransform.popFront();
	}
	queueToTransform = transformedQueue;
}

template<class T>
const T& Queue<T>::Iterator::operator*() const
{
	return this->queue->arr[this->index];
}

template<class T>
Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
	/*if (this->queue->end() == *this)
	{
		throw InvalidOperation();
	}*/

	++index;
	return *this;
}

template<class T>
Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
	Iterator result = *this;
	++* this;
	return result;
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& it) const
{
	if (queue == it.queue)
	{
		return index == it.index;
	}

	return false;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const
{
	bool ans = !(*this == it);
	return ans;
}

#endif //EX3_Queue_H

