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

class UndirectedGraph
{
private:
	class PrimsAlgorithmHelper
	{
	public:
		int vertexInMST;
		int vertexOutsideOfMST;
		int cost;

	public:
		PrimsAlgorithmHelper() : vertexInMST(-1), vertexOutsideOfMST(-1), cost(INT32_MIN)
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
			std::fill(costs[i].begin(), costs[i].end(), INT32_MIN);
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

	UndirectedGraph PrimsAlgorithm()
	{
		int randomVertex = rand() % numberOfVertices;

		if (!IsConnected(randomVertex))
		{
			throw std::runtime_error("Graph has to be connected");
		}

		UndirectedGraph mst(numberOfVertices);
		std::vector<bool> verticesInMST(numberOfVertices);
		PriorityQueue<PrimsAlgorithmHelper> priorityQueue;
		int currentVertex;

		currentVertex = randomVertex;
		verticesInMST[currentVertex] = true;

		for (int i = 0; i < numberOfVertices; i++)
		{
			if (adjacencyMatrix[currentVertex][i] != 0)
			{
				PrimsAlgorithmHelper pah;
				pah.vertexInMST = currentVertex;
				pah.vertexOutsideOfMST = i;
				pah.cost = costs[currentVertex][i];

				priorityQueue.put(pah, (-1) * pah.cost);
			}
		}

		while (std::find(verticesInMST.begin(), verticesInMST.end(), false) != verticesInMST.end())
		{
			PrimsAlgorithmHelper pah1 = priorityQueue.get().getValue();
			currentVertex = pah1.vertexOutsideOfMST;

			if (verticesInMST[currentVertex] == false)
			{
				verticesInMST[currentVertex] = true;

				mst.AddEdge(pah1.vertexInMST, pah1.vertexOutsideOfMST, pah1.cost);

				for (int i = 0; i < numberOfVertices; i++)
				{
					if (verticesInMST[i] == false && adjacencyMatrix[currentVertex][i] != 0)
					{
						PrimsAlgorithmHelper pah2;
						pah2.vertexInMST = currentVertex;
						pah2.vertexOutsideOfMST = i;
						pah2.cost = costs[currentVertex][i];

						priorityQueue.put(pah2, (-1) * pah2.cost);
					}
				}
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

		graph.AddEdge(0, 1, 4);
		graph.AddEdge(0, 2, 5);
		graph.AddEdge(1, 2, 3);
		graph.AddEdge(1, 3, 4);
		graph.AddEdge(2, 3, 2);
		graph.AddEdge(2, 4, 6);
		graph.AddEdge(2, 5, 1);
		graph.AddEdge(3, 4, 4);
		graph.AddEdge(3, 5, 2);
		graph.AddEdge(4, 5, 5);

		UndirectedGraph mst = graph.PrimsAlgorithm();

		std::cout << mst.GetEdgeSum() << "\n\n";

		mst.Display();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
