#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Stack
{
private:
	const int SIZE = 5;
	T* stack;
	int top;

public:
	Stack()
	{
		this->stack = new T[SIZE];
		this->top = -1;
	}

	~Stack()
	{
		delete[] stack;
	}

	bool IsEmpty()
	{
		return top == -1;
	}

	bool IsFull()
	{
		return top == SIZE - 1;
	}

	void Push(T value)
	{
		if (!IsFull())
		{
			top++;
			stack[top] = value;
		}
		else
		{
			throw std::runtime_error("Stack overflow");
		}
	}

	T Pop()
	{
		if (!IsEmpty())
		{
			return stack[top--];
		}
		else
		{
			throw std::runtime_error("Stack underflow");
		}
	}
};

template <typename T>
class Queue
{
private:
	const int SIZE = 6;
	T* queue;
	int first;
	int nextAvailableSpot;

public:
	Queue()
	{
		this->queue = new T[SIZE];
		this->first = -1;
		this->nextAvailableSpot = 0;
	}

	~Queue()
	{
		delete[] queue;
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
			throw std::runtime_error("Queue is full");
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
			throw std::runtime_error("Queue is empty");
		}
	}
};

template <typename T>
class Node
{
public:
	T value;
	Node* next;

	Node(T value) : value(value), next(nullptr)
	{

	}
};

template <typename T>
class LinkedList
{
public:
	Node<T>* head;

	LinkedList() : head(nullptr)
	{

	}

	~LinkedList()
	{
		DeleteLinkedList();
	}

	void AddAtBeginning(T value)
	{
		Node<T>* newNode = new Node<T>(value);
		newNode->next = head;
		head = newNode;
	}

	Node<T>* Find(T value)
	{
		Node<T>* foundNode = nullptr;
		Node<T>* currentNode = head;

		while (currentNode != nullptr)
		{
			if (currentNode->value == value)
			{
				foundNode = currentNode;
				break;
			}

			currentNode = currentNode->next;
		}

		return foundNode;
	}

	void Remove(T value)
	{
		Node<T>* currentNode = head;
		Node<T>* previousNode = nullptr;

		if (currentNode != nullptr && currentNode->value == value)
		{
			head = currentNode->next;
			delete currentNode;
		}
		else
		{
			while (currentNode != nullptr && currentNode->value != value)
			{
				previousNode = currentNode;
				currentNode = currentNode->next;
			}

			if (currentNode != nullptr && currentNode->value == value)
			{
				previousNode->next = currentNode->next;
				delete currentNode;
			}
		}
	}

	void DisplayLinkedList()
	{
		Node<T>* currentNode = head;

		while (currentNode != nullptr)
		{
			std::cout << currentNode->value << " -> ";
			currentNode = currentNode->next;
		}

		std::cout << "NULL" << std::endl;
	}

	void DeleteLinkedList()
	{
		Node<T>* currentNode = head;
		Node<T>* nextNode = nullptr;

		while (currentNode != nullptr)
		{
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}

		head = nullptr;
	}

	bool IsEmpty()
	{
		return head == nullptr;
	}

	std::vector<T> ToVector()
	{
		std::vector<T> vector;
		Node<T>* currentNode = head;

		while (currentNode != nullptr)
		{
			vector.push_back(currentNode->value);
			currentNode = currentNode->next;
		}

		return vector;
	}
};

class AdjacencyListGraph
{
private:
	std::vector<LinkedList<int>> adjacencyList;
	bool isDirected;
	int numberOfVertices;

public:
	AdjacencyListGraph(bool isDirected, int numberOfVertices) : isDirected(isDirected), numberOfVertices(numberOfVertices)
	{
		adjacencyList.resize(numberOfVertices);
	}

	bool InvalidVertex(int vertex)
	{
		return (vertex < 0) || (vertex >= numberOfVertices);
	}

	void AddEdge(int from, int to)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Adjacency list graph: invalid vertex number");
		}

		adjacencyList[from].AddAtBeginning(to);

		if (!isDirected)
		{
			adjacencyList[to].AddAtBeginning(from);
		}
	}

	std::vector<int> FindIsolatedVertices()
	{
		std::vector<int> isolatedVertices;
		bool isIsolated;

		for (int i = 0; i < numberOfVertices; i++)
		{
			isIsolated = true;

			if (!adjacencyList[i].IsEmpty())
			{
				isIsolated = false;
			}
			else
			{
				if (isDirected)
				{
					for (int j = 0; j < numberOfVertices; j++)
					{
						if ((j != i) && (adjacencyList[j].Find(i) != nullptr))
						{
							isIsolated = false;
							break;
						}
					}
				}
			}

			if (isIsolated)
			{
				isolatedVertices.push_back(i);
			}
		}

		return isolatedVertices;
	}

	void Display()
	{
		std::cout << "Adjacency lists:\n\n";

		for (int i = 0; i < numberOfVertices; i++)
		{
			std::cout << i << ": ";
			adjacencyList[i].DisplayLinkedList();
		}
	}

	void DFS(int startVertex)
	{
		if (InvalidVertex(startVertex))
		{
			throw std::runtime_error("DFS: invalid start vertex");
		}

		std::vector<bool> visitedVertices(numberOfVertices);
		Stack<int> stack;
		int currentVertex;
		std::vector<int> neighbors;

		stack.Push(startVertex);

		while (!stack.IsEmpty())
		{
			currentVertex = stack.Pop();
			visitedVertices[currentVertex] = true;
			neighbors = adjacencyList[currentVertex].ToVector();

			for (auto& neighbor : neighbors)
			{
				if (visitedVertices[neighbor] == false)
				{
					stack.Push(neighbor);
				}
			}

			std::cout << currentVertex << "  ";
		}

		std::cout << "\n";
	}

	void BFS(int startVertex)
	{
		if (InvalidVertex(startVertex))
		{
			throw std::runtime_error("DFS: invalid start vertex");
		}

		std::vector<bool> visitedVertices(numberOfVertices);
		Queue<int> queue;
		int currentVertex;
		std::vector<int> neighbors;

		queue.Enqueue(startVertex);

		while (!queue.IsEmpty())
		{
			currentVertex = queue.Dequeue();
			visitedVertices[currentVertex] = true;
			neighbors = adjacencyList[currentVertex].ToVector();

			for (auto& neighbor : neighbors)
			{
				if (visitedVertices[neighbor] == false)
				{
					queue.Enqueue(neighbor);
				}
			}

			std::cout << currentVertex << "  ";
		}

		std::cout << "\n";
	}
};

int main()
{
	AdjacencyListGraph graph(true, 6);

	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(0, 3);
	graph.AddEdge(2, 4);
	graph.AddEdge(2, 5);

	graph.Display();
	std::cout << "\n";

	graph.BFS(0);
	std::cout << "\n";

	return 0;
}
