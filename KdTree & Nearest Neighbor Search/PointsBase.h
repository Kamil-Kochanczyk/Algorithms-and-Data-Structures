#pragma once

#include "KdTree.h"

class PointsBase
{
private:
	KdTree base;

public:
	PointsBase(int k);

	void Insert(Point& point);
	Node* Search(Point& point);
	Node* FindClosestPoint(Point& point);
	void Display();
};
