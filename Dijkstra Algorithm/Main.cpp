#include <iostream>
#include <vector>

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

class ShortestPathInfo
{
private:
	int shortestPathFrom;
	int vertex;
	int shortestPath;
	int previousVertex;

public:
	ShortestPathInfo() : shortestPathFrom(-1), vertex(-1), shortestPath(-1), previousVertex(-1)
	{

	}

	void Display()
	{
		std::cout << vertex << "\t\t\t" << shortestPath << "\t\t\t" << previousVertex << "\n";
	}

	friend class Graph;
};

class Graph
{
private:
	std::vector<std::vector<int>> adjacencyMatrix;
	bool isDirected;
	int numberOfVertices;
	std::vector<std::vector<int>> costs;

public:
	Graph(bool isDirected, int numberOfVertices) : isDirected(isDirected), numberOfVertices(numberOfVertices)
	{
		adjacencyMatrix.resize(numberOfVertices);
		costs.resize(numberOfVertices);

		for (int i = 0; i < numberOfVertices; i++)
		{
			adjacencyMatrix[i].resize(numberOfVertices);
			costs[i].resize(numberOfVertices);
			std::fill(costs[i].begin(), costs[i].end(), -1);
		}
	}

	bool InvalidVertex(int vertex)
	{
		return vertex < 0 || vertex >= numberOfVertices;
	}

	void AddEdge(int from, int to, int cost)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Invalid vertex number");
		}

		if (cost < 0)
		{
			throw std::runtime_error("Cost cannot be negative");
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

		costs[from][to] = cost;

		if (!isDirected)
		{
			costs[to][from] = cost;
		}
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

		std::cout << "\n";

		std::cout << "Costs:\n\n";

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = 0; j < numberOfVertices; j++)
			{
				if (costs[i][j] >= 0)
				{
					std::cout << i << " -> " << j << ": " << costs[i][j] << "\n";
				}
			}
		}
	}

	std::vector<ShortestPathInfo> DijkstraAlgorithm(int startVertex)
	{
		if (InvalidVertex(startVertex))
		{
			throw std::runtime_error("Invalid vertex");
		}

		std::vector<ShortestPathInfo> result(numberOfVertices);
		PriorityQueue<int> unvisited;
		std::vector<bool> visited(numberOfVertices);
		std::vector<int> neighbors;

		for (int i = 0; i < result.size(); i++)
		{
			result[i].shortestPathFrom = startVertex;
			result[i].vertex = i;

			if (i == startVertex)
			{
				result[i].shortestPath = 0;
			}
			else
			{
				result[i].shortestPath = INT32_MAX;
			}

			unvisited.put(i, (-1) * result[i].shortestPath);
		}

		while (std::find(visited.begin(), visited.end(), false) != visited.end())
		{
			int currentVertex = unvisited.get().getValue();

			for (int i = 0; i < numberOfVertices; i++)
			{
				if (adjacencyMatrix[currentVertex][i] != 0)
				{
					neighbors.push_back(i);
				}
			}

			for (auto& neighbor : neighbors)
			{
				if (visited[neighbor] == false)
				{
					int distance = result[currentVertex].shortestPath + costs[currentVertex][neighbor];

					if (distance < result[neighbor].shortestPath)
					{
						result[neighbor].shortestPath = distance;
						result[neighbor].previousVertex = currentVertex;

						unvisited.put(neighbor, (-1) * distance);
					}
				}
			}

			visited[currentVertex] = true;
			neighbors.clear();
		}

		return result;
	}
};

int main()
{
	Graph graph(true, 5);

	graph.AddEdge(0, 1, 1);
	graph.AddEdge(0, 3, 2);
	graph.AddEdge(1, 2, 2);
	graph.AddEdge(2, 3, 2);
	graph.AddEdge(2, 4, 8);
	graph.AddEdge(3, 2, 2);
	graph.AddEdge(3, 4, 3);

	std::vector<ShortestPathInfo> result = graph.DijkstraAlgorithm(0);

	for (int i = 0; i < result.size(); i++)
	{
		result[i].Display();
	}

	std::cout << "\n";

	return 0;
}
