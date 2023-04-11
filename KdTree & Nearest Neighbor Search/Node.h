#pragma once

#include "Point.h"
#include "KdTree.h"

class KdTree;

class Node
{
private:
	Point point;
	Node* left;
	Node* right;

public:
	Node(Point& point);

	const Point& GetPoint() const;

	friend class KdTree;
};
