#include "Queue.h"

static bool isEven(int n)
{
	return (n % 2) == 0;
}

template<class T, class Condition>
Queue<T> filter(Queue<T> queueToFilter, Condition c)
{
	Queue<T> filteredQueue;
	for (Queue<int>::Iterator it = queueToFilter.begin(); it != queueToFilter.end(); ++it)
	{
		if (c(*it))
		{
			filteredQueue.pushBack(*it);
		}
	}
	return filteredQueue;
}

int main()
{
	/* some code... */
	Queue<int> queue3;
	for (int i = 1; i <= 10; i++) {
		queue3.pushBack(i);
	}
	Queue<int> queue4 = filter(queue3, isEven);
}
