#include <iostream>
#include <vector>

template <typename T>
class Stack
{
private:
	const int SIZE = 100;
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
class Node
{
private:
	T value;
	int priority;

public:
	Node(T value, int priority) : value(value), priority(priority)
	{

	}

	T getValue()
	{
		return value;
	}

	int getPriority()
	{
		return priority;
	}
};

template <typename T>
class PriorityQueue
{
private:
	std::vector<Node<T>> maxHeap;

public:
	void put(T value, int priority)
	{
		Node<T> newNode(value, priority);
		maxHeap.push_back(newNode);

		if (maxHeap.size() > 1)
		{
			int newNodeIndex = maxHeap.size() - 1;
			compareChildWithParent(newNodeIndex);
		}
	}

	Node<T> get()
	{
		if (isEmpty())
		{
			throw std::runtime_error("Priority queue is empty");
		}

		Node<T> node = front();
		maxHeap[0] = maxHeap[maxHeap.size() - 1];
		maxHeap.pop_back();
		heapify(0);

		return node;
	}

	Node<T> front()
	{
		if (isEmpty())
		{
			throw std::runtime_error("Priority queue is empty");
		}

		return maxHeap[0];
	}

	bool isEmpty()
	{
		return maxHeap.empty();
	}

	void makeNull()
	{
		maxHeap.clear();
	}

private:
	void compareChildWithParent(int childIndex)
	{
		if (childIndex > 0)
		{
			bool isLeftChild = false;
			bool isRightChild = false;
			double parentIndexIfLeftChild = (childIndex - 1) / 2.0;
			double parentIndexIfRightChild = (childIndex - 2) / 2.0;
			double parentIndex;

			if (parentIndexIfLeftChild == floor(parentIndexIfLeftChild))
			{
				isLeftChild = true;
			}
			else if (parentIndexIfRightChild == floor(parentIndexIfRightChild))
			{
				isRightChild = true;
			}

			if (isLeftChild)
			{
				parentIndex = parentIndexIfLeftChild;
			}
			else if (isRightChild)
			{
				parentIndex = parentIndexIfRightChild;
			}

			if (maxHeap[childIndex].getPriority() > maxHeap[parentIndex].getPriority())
			{
				std::swap(maxHeap[childIndex], maxHeap[parentIndex]);
				compareChildWithParent(parentIndex);
			}
		}
	}

	void heapify(int index)
	{
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int largest = index;

		if (leftChild < maxHeap.size() && maxHeap[leftChild].getPriority() > maxHeap[largest].getPriority())
		{
			largest = leftChild;
		}

		if (rightChild < maxHeap.size() && maxHeap[rightChild].getPriority() > maxHeap[largest].getPriority())
		{
			largest = rightChild;
		}

		if (largest != index)
		{
			std::swap(maxHeap[index], maxHeap[largest]);
			heapify(largest);
		}
	}
};

// disjoint sets <=> separate trees
// set representative <=> tree root
class DisjointSet
{
private:
	std::vector<int> parent;
	int numberOfElements;

public:
	DisjointSet(int numberOfElements) : numberOfElements(numberOfElements)
	{
		for (int i = 0; i < numberOfElements; i++)
		{
			parent.push_back(i);
		}
	}

	bool IsElementValid(int element)
	{
		return element >= 0 && element < numberOfElements;
	}

	int FindRepresentative(int element)
	{
		if (!IsElementValid(element))
		{
			throw std::runtime_error("Invalid element");
		}

		if (parent[element] == element)
		{
			return element;
		}
		else
		{
			return FindRepresentative(parent[element]);
		}
	}

	bool AreInTheSameSet(int u, int v)
	{
		if ((!IsElementValid(u)) || (!IsElementValid(v)))
		{
			throw std::runtime_error("Invalid element");
		}

		return FindRepresentative(u) == FindRepresentative(v);
	}

	void MergeSets(int set1Element, int set2Element)
	{
		if ((!IsElementValid(set1Element)) || (!IsElementValid(set2Element)))
		{
			throw std::runtime_error("Invalid element");
		}

		int set1Representative = FindRepresentative(set1Element);
		int set2Representative = FindRepresentative(set2Element);
		parent[set2Representative] = set1Representative;
	}

	bool IsOnlyOneSet()
	{
		bool isOnlyOneSet = true;

		for (int i = 0; i < numberOfElements; i++)
		{
			for (int j = 0; j < numberOfElements; j++)
			{
				if (!AreInTheSameSet(i, j))
				{
					isOnlyOneSet = false;
					break;
				}
			}
		}

		return isOnlyOneSet;
	}

	void Display()
	{
		for (int i = 0; i < numberOfElements; i++)
		{
			std::cout << i << ": " << parent[i] << "\n";
		}

		std::cout << "\n";
	}
};

class UndirectedGraph
{
private:
	class UndirectedEdge
	{
	public:
		int vertex1;
		int vertex2;
		int cost;

	public:
		UndirectedEdge() : vertex1(-1), vertex2(-1), cost(INT32_MIN)
		{

		}
	};

private:
	int numberOfVertices;
	std::vector<std::vector<int>> adjacencyMatrix;
	std::vector<std::vector<int>> costs;

public:
	UndirectedGraph(int numberOfVertices) : numberOfVertices(numberOfVertices)
	{
		adjacencyMatrix.resize(numberOfVertices);
		costs.resize(numberOfVertices);

		for (int i = 0; i < numberOfVertices; i++)
		{
			adjacencyMatrix[i].resize(numberOfVertices);
			costs[i].resize(numberOfVertices);
			std::fill(costs[i].begin(), costs[i].end(), -INT32_MIN);
		}
	}

	bool InvalidVertex(int vertex)
	{
		return (vertex < 0) || (vertex >= numberOfVertices);
	}

	void AddEdge(int from, int to, int cost)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Invalid vertex number");
		}

		if (from == to)
		{
			adjacencyMatrix[from][to] = 2;
		}
		else
		{
			adjacencyMatrix[from][to] = adjacencyMatrix[to][from] = 1;
		}

		costs[from][to] = costs[to][from] = cost;
	}

	bool IsConnected(int startVertex)
	{
		if (InvalidVertex(startVertex))
		{
			throw std::runtime_error("Invalid start vertex");
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

			for (int i = 0; i < numberOfVertices; i++)
			{
				if (adjacencyMatrix[currentVertex][i] != 0)
				{
					neighbors.push_back(i);
				}
			}

			for (auto& neighbor : neighbors)
			{
				if (visitedVertices[neighbor] == false)
				{
					stack.Push(neighbor);
				}
			}

			neighbors.clear();
		}

		return std::find(visitedVertices.begin(), visitedVertices.end(), false) == visitedVertices.end();
	}

	UndirectedGraph KruskalsAlgorithm()
	{
		if (!IsConnected(rand() % numberOfVertices))
		{
			throw std::runtime_error("Graph has to be connected");
		}

		UndirectedGraph mst(numberOfVertices);
		DisjointSet ds(numberOfVertices);
		PriorityQueue<UndirectedEdge> pq;

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = i; j < numberOfVertices; j++)
			{
				if (adjacencyMatrix[i][j] != 0)
				{
					UndirectedEdge edge;
					edge.vertex1 = i;
					edge.vertex2 = j;
					edge.cost = costs[i][j];

					pq.put(edge, (-1) * edge.cost);
				}
			}
		}

		while ((!pq.isEmpty()) && (!ds.IsOnlyOneSet()))
		{
			UndirectedEdge edge = pq.get().getValue();

			if (!ds.AreInTheSameSet(edge.vertex1, edge.vertex2))
			{
				ds.MergeSets(edge.vertex1, edge.vertex2);

				mst.AddEdge(edge.vertex1, edge.vertex2, edge.cost);
			}
		}

		return mst;
	}

	int GetEdgeSum()
	{
		int sum = 0;

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = i; j < numberOfVertices; j++)
			{
				if (adjacencyMatrix[i][j] != 0)
				{
					sum += costs[i][j];
				}
			}
		}

		return sum;
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

int main()
{
	srand(time(0));

	try
	{
		UndirectedGraph graph(6);

		graph.AddEdge(0, 1, 1);
		graph.AddEdge(0, 3, 4);
		graph.AddEdge(0, 4, 3);
		graph.AddEdge(1, 3, 4);
		graph.AddEdge(1, 4, 2);
		graph.AddEdge(3, 4, 4);
		graph.AddEdge(2, 4, 4);
		graph.AddEdge(2, 5, 5);
		graph.AddEdge(4, 5, 7);

		UndirectedGraph mst = graph.KruskalsAlgorithm();

		std::cout << mst.GetEdgeSum() << "\n\n";

		mst.Display();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
