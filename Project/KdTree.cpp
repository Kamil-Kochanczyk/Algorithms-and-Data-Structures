#include "KdTree.h"

KdTree::KdTree(int k) : root(nullptr), k(k)
{
	if (k <= 0)
	{
		throw std::runtime_error("k has to be a positive integer.");
	}
}

KdTree::~KdTree()
{
	DeleteEverything(root);
}

Node* KdTree::GetRoot() const
{
	return root;
}

void KdTree::Insert(Point& point)
{
	if (point.GetNumberOfDimensions() != k)
	{
		throw std::runtime_error("Insert error: point has wrong number of coordinates.");
	}
	else
	{
		InsertRecursively(root, point, 0);
	}
}

Node* KdTree::Search(Point& point)
{
	return SearchRecursively(root, point, 0);
}

Node* KdTree::FindClosestPoint(Point& point)
{
	if (point.GetNumberOfDimensions() != k)
	{
		throw std::runtime_error("FindClosestPoint error: point has wrong number of coordinates.");
	}
	else
	{
		return FindNearestNeighbor(root, point, nullptr, 0);
	}
}

void KdTree::PreorderDisplay(Node* node)
{
	if (node != nullptr)
	{
		node->point.Display();
		std::cout << std::endl;

		if (node->left != nullptr)
		{
			PreorderDisplay(node->left);
		}

		if (node->right != nullptr)
		{
			PreorderDisplay(node->right);
		}
	}
}

void KdTree::InsertRecursively(Node*& root, Point& point, int depth)
{
	if (root == nullptr)
	{
		Node* newNode = new Node(point);
		root = newNode;
	}
	else
	{
		int currentCoordinate = depth % k;

		if (point.GetCoordinates()[currentCoordinate] < root->point.GetCoordinates()[currentCoordinate])
		{
			InsertRecursively(root->left, point, depth + 1);
		}
		else
		{
			InsertRecursively(root->right, point, depth + 1);
		}
	}
}

Node* KdTree::SearchRecursively(Node* root, Point& point, int depth)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (root->GetPoint().IsTheSameAs(point))
	{
		return root;
	}

	int currentCoordinate = depth % k;

	if (point.GetCoordinates()[currentCoordinate] < root->GetPoint().GetCoordinates()[currentCoordinate])
	{
		return SearchRecursively(root->left, point, depth + 1);
	}

	return SearchRecursively(root->right, point, depth + 1);
}

Node* KdTree::FindNearestNeighbor(Node* root, Point& point, Node* closestSoFar, int depth)
{
	if (root == nullptr)
	{
		return closestSoFar;
	}

	if (closestSoFar == nullptr)
	{
		closestSoFar = root;
	}
	else
	{
		if (root->point.GetDistanceSquared(point) < closestSoFar->point.GetDistanceSquared(point))
		{
			closestSoFar = root;
		}
	}

	int currentCoordinate = depth % k;
	Node* goodSide = nullptr;
	Node* badSide = nullptr;

	if (point.GetCoordinates()[currentCoordinate] < root->point.GetCoordinates()[currentCoordinate])
	{
		goodSide = root->left;
		badSide = root->right;
	}
	else
	{
		goodSide = root->right;
		badSide = root->left;
	}

	closestSoFar = FindNearestNeighbor(goodSide, point, closestSoFar, depth + 1);

	double difference = point.GetCoordinates()[currentCoordinate] - root->point.GetCoordinates()[currentCoordinate];

	if ((difference * difference) < closestSoFar->point.GetDistanceSquared(point))
	{
		closestSoFar = FindNearestNeighbor(badSide, point, closestSoFar, depth + 1);
	}

	return closestSoFar;
}

void KdTree::DeleteEverything(Node*& root)
{
	if (root != nullptr)
	{
		if (root->left != nullptr)
		{
			DeleteEverything(root->left);
		}

		if (root->right != nullptr)
		{
			DeleteEverything(root->right);
		}

		delete root;
		root = nullptr;
	}
}
