#include <iostream>

template <typename T>
class ArrayQueue
{
private:
	const int SIZE = 6;
	T* queue;
	int first;
	int nextAvailableSpot;

public:
	ArrayQueue()
	{
		this->queue = new T[SIZE];
		this->first = -1;
		this->nextAvailableSpot = 0;
		std::cout << "ArrayQueue created, SIZE = " << SIZE << std::endl;
	}

	~ArrayQueue()
	{
		delete[] queue;
		std::cout << "ArrayQueue destroyed" << std::endl;
	}

	bool IsEmpty()
	{
		return first == -1;
	}

	bool IsFull()
	{
		return nextAvailableSpot == first;
	}

	void Enqueue(T value)
	{
		if (!IsFull())
		{
			if (IsEmpty())
			{
				first = nextAvailableSpot;
			}

			queue[nextAvailableSpot] = value;
			nextAvailableSpot = (nextAvailableSpot + 1) % SIZE;
		}
		else
		{
			throw std::exception("ArrayQueue is full");
		}
	}

	T Dequeue()
	{
		if (!IsEmpty())
		{
			T valueAtTheBeginning = queue[first];
			first = (first + 1) % SIZE;
			first = (first == nextAvailableSpot) ? -1 : first;
			return valueAtTheBeginning;
		}
		else
		{
			throw std::exception("ArrayQueue is empty");
		}
	}
};

template <typename T>
class TestQueue
{
private:
	const int SIZE = 6;
	T* queue;
	int front;
	int rear;

public:
	TestQueue()
	{
		this->queue = new T[SIZE];
		this->front = -1;
		this->rear = -1;
		std::cout << "TestQueue created, SIZE = " << SIZE << std::endl;
	}

	~TestQueue()
	{
		delete[] queue;
		std::cout << "TestQueue destroyed" << std::endl;
	}

	bool IsEmpty()
	{
		return front == -1;
	}

	bool IsFull()
	{
		return ((rear + 1) % SIZE) == front;
	}

	void Enqueue(T value)
	{
		if (IsEmpty())
		{
			front = 0;
			rear = 0;
			queue[front] = value;
		}
		else
		{
			if (!IsFull())
			{
				rear = (rear + 1) % SIZE;
				queue[rear] = value;
			}
			else
			{
				throw std::exception("TestQueue is full");
			}
		}
	}

	T Dequeue()
	{
		if (!IsEmpty())
		{
			T valueAtTheBeginning = queue[front];
			
			if (front == rear)
			{
				front = -1;
				rear = -1;
			}
			else
			{
				front = (front + 1) % SIZE;
			}
			
			return valueAtTheBeginning;
		}
		else
		{
			throw std::exception("TestQueue is empty");
		}
	}
};

template <typename T>
class Node
{
public:
	T value;
	Node* next;

	Node(T value)
	{
		this->value = value;
		this->next = nullptr;
	}
};

template <typename T>
class PointerQueue
{
private:
	const int SIZE = 7;
	int counter;
	Node<T>* beginning;
	Node<T>* end;

public:
	PointerQueue()
	{
		this->counter = 0;
		this->beginning = nullptr;
		this->end = nullptr;
		std::cout << "PointerQueue created, SIZE = " << SIZE << std::endl;
	}

	~PointerQueue()
	{
		while (!IsEmpty())
		{
			Dequeue();
		}

		std::cout << "PointerQueue destroyed" << std::endl;
	}

	bool IsEmpty()
	{
		return beginning == nullptr;
	}

	bool IsFull()
	{
		return counter == SIZE;
	}

	void Enqueue(T value)
	{
		if (!IsFull())
		{
			Node<T>* newNode = new Node<T>(value);

			if (IsEmpty())
			{
				beginning = newNode;
			}
			else
			{
				end->next = newNode;
			}

			end = newNode;
			counter++;
		}
		else
		{
			throw std::exception("PointerQueue is full");
		}
	}

	T Dequeue()
	{
		if (!IsEmpty())
		{
			T valueAtTheBeginning = beginning->value;
			Node<T>* nodeAtTheBeginning = beginning;
			beginning = beginning->next;
			delete nodeAtTheBeginning;
			counter--;
			return valueAtTheBeginning;
		}
		else
		{
			throw std::exception("PointerQueue is empty");
		}
	}
};

int main()
{
	ArrayQueue<double> aq;
	std::cout << std::endl;

	try
	{
		for (int i = 0; i > -10; i--)
		{
			aq.Enqueue((double)i);
			std::cout << "Enqueued: " << i << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		double dequeued;

		for (int i = -10; i > -100; i--)
		{
			dequeued = aq.Dequeue();
			std::cout << "Dequeued: " << dequeued << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	TestQueue<double> tq;
	std::cout << std::endl;

	try
	{
		for (int i = 0; i > -10; i--)
		{
			tq.Enqueue((double)i);
			std::cout << "Enqueued: " << i << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		double dequeued;

		for (int i = -10; i > -100; i--)
		{
			dequeued = tq.Dequeue();
			std::cout << "Dequeued: " << dequeued << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	PointerQueue<char> pq;
	std::cout << std::endl;

	try
	{
		for (char c = 'a'; c <= 'z'; c++)
		{
			pq.Enqueue(c);
			std::cout << "Enqueued: " << c << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		char dequeued;

		for (int i = 0; i < 100; i++)
		{
			dequeued = pq.Dequeue();
			std::cout << "Dequeued: " << dequeued << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	return 0;
}
