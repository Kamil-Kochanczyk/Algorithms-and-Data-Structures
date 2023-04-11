#include "PointsBase.h"

PointsBase::PointsBase(int k) : base(k)
{

}

void PointsBase::Insert(Point& point)
{
	base.Insert(point);
}

Node* PointsBase::Search(Point& point)
{
	return base.Search(point);
}

Node* PointsBase::FindClosestPoint(Point& point)
{
	return base.FindClosestPoint(point);
}

void PointsBase::Display()
{
	std::cout << "Points in base:\n" << std::endl;
	base.PreorderDisplay(base.GetRoot());
	std::cout << "\nEnd of base" << std::endl;
}
