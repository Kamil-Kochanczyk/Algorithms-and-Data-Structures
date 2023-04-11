#pragma once

#include "Node.h"

class Node;

class KdTree
{
private:
	Node* root;
	int k;

public:
	KdTree(int k);
	~KdTree();

	Node* GetRoot() const;

	void Insert(Point& point);
	Node* Search(Point& point);
	Node* FindClosestPoint(Point& point);
	void PreorderDisplay(Node* node);

private:
	void InsertRecursively(Node*& root, Point& point, int depth);
	Node* SearchRecursively(Node* root, Point& point, int depth);
	Node* FindNearestNeighbor(Node* root, Point& point, Node* closestSoFar, int depth);
	void DeleteEverything(Node*& root);
};
