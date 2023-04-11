#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class AdjacencyMatrixGraph
{
private:
	std::vector<std::vector<int>> adjacencyMatrix;
	bool isDirected;
	int numberOfVertices;

public:
	AdjacencyMatrixGraph(bool isDirected, int numberOfVertices) : isDirected(isDirected), numberOfVertices(numberOfVertices)
	{
		adjacencyMatrix.resize(numberOfVertices);

		for (auto& row : adjacencyMatrix)
		{
			row.resize(numberOfVertices);
		}
	}

	bool InvalidVertex(int vertex)
	{
		return vertex < 0 || vertex >= numberOfVertices;
	}

	void AddEdge(int from, int to)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Adjacency matrix graph: invalid vertex number");
		}

		if (from == to)
		{
			adjacencyMatrix[from][to] = 2;
		}
		else
		{
			if (isDirected)
			{
				adjacencyMatrix[from][to] = 1;
			}
			else
			{
				adjacencyMatrix[from][to] = adjacencyMatrix[to][from] = 1;
			}
		}
	}

	std::vector<int> FindIsolatedVertices()
	{
		std::vector<int> isolatedVertices;
		bool isIsolated;

		for (int i = 0; i < numberOfVertices; i++)
		{
			isIsolated = true;

			for (int j = 0; j < numberOfVertices; j++)
			{
				if (adjacencyMatrix[i][j] != 0)
				{
					isIsolated = false;
					break;
				}
			}

			if (isIsolated && isDirected)
			{
				for (int k = 0; k < numberOfVertices; k++)
				{
					if (adjacencyMatrix[k][i] != 0)
					{
						isIsolated = false;
						break;
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
		std::cout << "Adjacency matrix:\n\n";

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = 0; j < numberOfVertices; j++)
			{
				std::cout << adjacencyMatrix[i][j] << "  ";
			}

			std::cout << "\n";
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
		return vertex < 0 || vertex >= numberOfVertices;
	}

	void AddEdge(int from, int to)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Adjacency list graph: invalid vertex number");
		}

		adjacencyList[from].AddAtBeginning(to);

		if (!isDirected && from != to)
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
};

class IncidenceMatrixGraph
{
private:
	std::vector<std::vector<int>> incidenceMatrix;
	bool isDirected;
	int numberOfVertices;
	int edgesCounter = 0;
	int availableEdges = 25;

public:
	IncidenceMatrixGraph(bool isDirected, int numberOfVertices) : isDirected(isDirected), numberOfVertices(numberOfVertices)
	{
		incidenceMatrix.resize(numberOfVertices);

		for (auto& row : incidenceMatrix)
		{
			row.resize(availableEdges);
		}
	}

	bool InvalidVertex(int vertex)
	{
		return vertex < 0 || vertex >= numberOfVertices;
	}

	void AddEdge(int from, int to)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Incidence matrix graph: invalid vertex number");
		}

		if (edgesCounter >= availableEdges)
		{
			AddMoreAvailableEdges();
		}

		int currentEdge = edgesCounter;

		if (from == to)
		{
			incidenceMatrix[from][currentEdge] = 2;	// <=> incidenceMatrix[to][currentEdge] = 2;
		}
		else
		{
			if (isDirected)
			{
				incidenceMatrix[from][currentEdge] = 1;
				incidenceMatrix[to][currentEdge] = -1;
			}
			else
			{
				incidenceMatrix[from][currentEdge] = incidenceMatrix[to][currentEdge] = 1;
			}
		}

		edgesCounter++;
	}

	std::vector<int> FindIsolatedVertices()
	{
		std::vector<int> isolatedVertices;
		bool isIsolated;

		for (int i = 0; i < numberOfVertices; i++)
		{
			isIsolated = true;

			for (int j = 0; j < edgesCounter; j++)
			{
				if (incidenceMatrix[i][j] != 0)
				{
					isIsolated = false;
					break;
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
		std::cout << "Incidence matrix:\n\n";

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = 0; j < edgesCounter; j++)
			{
				if (incidenceMatrix[i][j] == -1)
				{
					std::cout << incidenceMatrix[i][j] << "  ";
				}
				else
				{
					std::cout << " " << incidenceMatrix[i][j] << "  ";
				}
			}

			std::cout << "\n";
		}
	}

private:
	void AddMoreAvailableEdges()
	{
		availableEdges *= 2;

		for (auto& row : incidenceMatrix)
		{
			row.resize(availableEdges);
		}
	}
};

int main()
{
	bool isDirected;
	int numberOfVertices;

	std::cout << "Undirected graph - 0\n";
	std::cout << "Directed graph - 1\n";
	std::cout << "Choose the type of your graph: ";
	std::cin >> isDirected;
	std::cout << "\n";

	std::cout << "Choose the number of vertices in your graph: ";
	std::cin >> numberOfVertices;
	std::cout << "\n";

	AdjacencyMatrixGraph am(isDirected, numberOfVertices);
	AdjacencyListGraph al(isDirected, numberOfVertices);
	IncidenceMatrixGraph im(isDirected, numberOfVertices);

	std::cout << "Specify the edges in your graph\n\n";

	std::cout << "For example:\n";
	std::cout << "3,1 - edge from vertex 3 to vertex 1\n";
	std::cout << "4,2 - edge from vertex 4 to vertex 2\n";
	std::cout << "0,0 - edge from vertex 0 to vertex 0 (self loop)\n\n";

	std::cout << "There should be no space between the numbers, just comma\n";
	std::cout << "Vertices are numbered starting with 0\n";
	std::cout << "For example, if a graph has 5 vertices, we reference them by numbers 0, 1, 2, 3, 4\n\n";

	std::cout << "If you are done, type \"stop\"\n\n";

	int from;
	int to;
	std::string stop = "stop";
	std::string pairOfVertices;

	do
	{
		std::cin >> pairOfVertices;

		if (pairOfVertices != stop)
		{
			// Extracting numbers (vertices) from string
			int commaPosition = pairOfVertices.find(",");
			from = std::stoi(pairOfVertices.substr(0, commaPosition));
			to = std::stoi(pairOfVertices.substr(commaPosition + 1, pairOfVertices.length() - (commaPosition + 1)));
			
			try
			{
				am.AddEdge(from, to);
				al.AddEdge(from, to);
				im.AddEdge(from, to);
			}
			catch (const std::runtime_error& e)
			{
				std::cout << e.what() << "\n";
			}
		}
	}
	while (pairOfVertices != stop);
	std::cout << "\n";

	if (isDirected)
	{
		std::cout << "Directed graph\n\n";
	}
	else
	{
		std::cout << "Undirected graph\n\n";
	}

	std::cout << "Number of vertices: " << numberOfVertices << "\n\n";

	am.Display();
	std::cout << "\n";
	al.Display();
	std::cout << "\n";
	im.Display();
	std::cout << "\n";

	std::vector<int> isolatedVertices = am.FindIsolatedVertices();
	/*std::vector<int> isolatedVertices = al.FindIsolatedVertices();
	std::vector<int> isolatedVertices = im.FindIsolatedVertices();*/

	std::cout << "Isolated vertices: ";
	for (int vertex : isolatedVertices)
	{
		std::cout << vertex << ", ";
	}
	std::cout << "\n";

	return 0;
}
