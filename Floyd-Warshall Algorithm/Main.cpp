#include <iostream>
#include <vector>

void DisplayMatrix(std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] < 0)
			{
				std::cout << matrix[i][j] << "  ";
			}
			else
			{
				std::cout << " " << matrix[i][j] << "  ";
			}
		}

		std::cout << "\n";
	}
}

void DisplayVector(std::vector<int> vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << "  ";
	}

	std::cout << "\n";
}

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
			std::fill(costs[i].begin(), costs[i].end(), INT32_MIN);
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

	std::vector<std::vector<std::vector<int>>> FloydWarshallAlgorithm()
	{
		int inf = INT32_MAX / 16;

		std::vector<std::vector<int>> shortestPathsMatrix;
		std::vector<std::vector<int>> previousMatrix;

		shortestPathsMatrix.resize(numberOfVertices);
		previousMatrix.resize(numberOfVertices);

		for (int i = 0; i < numberOfVertices; i++)
		{
			shortestPathsMatrix[i].resize(numberOfVertices);
			previousMatrix[i].resize(numberOfVertices);
		}

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = 0; j < numberOfVertices; j++)
			{
				if (i == j)
				{
					shortestPathsMatrix[i][j] = 0;
					previousMatrix[i][j] = i;
				}
				else if (costs[i][j] != INT32_MIN)
				{
					shortestPathsMatrix[i][j] = costs[i][j];
					previousMatrix[i][j] = i;
				}
				else
				{
					shortestPathsMatrix[i][j] = inf;
					previousMatrix[i][j] = -1;
				}
			}
		}

		for (int i = 0; i < numberOfVertices; i++)
		{
			for (int j = 0; j < numberOfVertices; j++)
			{
				for (int k = 0; k < numberOfVertices; k++)
				{
					int distance = shortestPathsMatrix[j][i] + shortestPathsMatrix[i][k];

					if (distance < shortestPathsMatrix[j][k])
					{
						if (shortestPathsMatrix[j][i] != inf && shortestPathsMatrix[i][k] != inf)
						{
							shortestPathsMatrix[j][k] = distance;
							previousMatrix[j][k] = previousMatrix[i][k];
						}
					}
				}
			}

			for (int l = 0; l < numberOfVertices; l++)
			{
				if (shortestPathsMatrix[l][l] < 0)
				{
					throw std::runtime_error("Negative cycle");
				}
			}
		}

		std::vector<std::vector<std::vector<int>>> matrices;
		matrices.push_back(shortestPathsMatrix);
		matrices.push_back(previousMatrix);

		return matrices;
	}

	std::vector<int> ReconstructPath(int from, int to, std::vector<std::vector<int>> previousMatrix)
	{
		if (InvalidVertex(from) || InvalidVertex(to))
		{
			throw std::runtime_error("Invalid vertex number");
		}

		std::vector<int> path;

		if (previousMatrix[from][to] == -1)
		{
			return path;
		}

		path.push_back(to);

		while (to != from)
		{
			to = previousMatrix[from][to];
			path.push_back(to);
		}

		std::reverse(path.begin(), path.end());

		return path;
	}
};

int main()
{
	Graph graph(true, 4);

	graph.AddEdge(0, 2, -2);
	graph.AddEdge(2, 3, 2);
	graph.AddEdge(3, 1, -1);
	graph.AddEdge(1, 0, 4);
	graph.AddEdge(1, 2, 3);

	try
	{
		std::vector<std::vector<std::vector<int>>> result = graph.FloydWarshallAlgorithm();
		std::vector<std::vector<int>> shortestPathsMatrix = result[0];
		std::vector<std::vector<int>> previousMatrix = result[1];

		DisplayMatrix(shortestPathsMatrix);
		std::cout << "\n";
		DisplayMatrix(previousMatrix);
		std::cout << "\n";

		int from = 0;
		int to = 3;
		std::vector<int> path = graph.ReconstructPath(from, to, previousMatrix);

		DisplayVector(path);
		std::cout << "\n";
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

	return 0;
}
