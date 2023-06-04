#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Queue
{
private:
	const int SIZE = 100;
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
			throw std::exception("Queue is full");
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
			throw std::exception("Queue is empty");
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

	AdjacencyListGraph(AdjacencyListGraph& graph) : isDirected(graph.isDirected), numberOfVertices(graph.numberOfVertices)
	{
		this->adjacencyList.resize(this->numberOfVertices);

		for (int i = 0; i < graph.numberOfVertices; i++)
		{
			Node<int>* currentNode = graph.adjacencyList[i].head;

			while (currentNode != nullptr)
			{
				this->adjacencyList[i].AddAtBeginning(currentNode->value);
				currentNode = currentNode->next;
			}
		}
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

	std::vector<int> TopologicalSort();
};

std::vector<int> AdjacencyListGraph::TopologicalSort()
{
	if (!isDirected)
	{
		throw std::runtime_error("Error: graph is not directed");
	}

	std::vector<std::vector<int>> graphRepresentation(numberOfVertices);
	std::vector<int> inDegrees(numberOfVertices);
	Queue<int> queue;
	std::vector<int> result;

	for (int i = 0; i < numberOfVertices; i++)
	{
		graphRepresentation[i] = adjacencyList[i].ToVector();
	}

	for (auto& vertex : graphRepresentation)
	{
		for (auto& neighbor : vertex)
		{
			inDegrees[neighbor]++;
		}
	}

	for (int i = 0; i < numberOfVertices; i++)
	{
		if (inDegrees[i] == 0)
		{
			queue.Enqueue(i);
		}
	}

	while (!queue.IsEmpty())
	{
		int vertex = queue.Dequeue();
		result.push_back(vertex);

		for (auto& neighbor : graphRepresentation[vertex])
		{
			inDegrees[neighbor]--;

			if (inDegrees[neighbor] == 0)
			{
				queue.Enqueue(neighbor);
			}
		}
	}

	for (auto& value : inDegrees)
	{
		if (value > 0)
		{
			throw std::runtime_error("Error: graph is not acyclic");
		}
	}

	return result;
}

int main()
{
	AdjacencyListGraph graph(true, 7);

	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(1, 2);
	graph.AddEdge(1, 5);
	graph.AddEdge(2, 3);
	graph.AddEdge(5, 3);
	graph.AddEdge(5, 4);
	graph.AddEdge(6, 1);
	graph.AddEdge(6, 5);

	try
	{
		std::vector<int> result = graph.TopologicalSort();

		for (auto& element : result)
		{
			std::cout << element << ", ";
		}

		std::cout << "\n";
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}

	return 0;
}
