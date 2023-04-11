#include "Node.h"

Node::Node(Point& point) : point(point), left(nullptr), right(nullptr)
{

}

const Point& Node::GetPoint() const
{
	return point;
}
