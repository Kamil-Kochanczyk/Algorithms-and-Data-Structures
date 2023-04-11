#include "Point.h"

Point::Point(std::vector<double>& coordinates) : coordinates(coordinates), numberOfDimensions(coordinates.size())
{

}

const std::vector<double>& Point::GetCoordinates() const
{
	return coordinates;
}

int Point::GetNumberOfDimensions() const
{
	return numberOfDimensions;
}

double Point::GetDistanceSquared(const Point& point) const
{
	if (point.numberOfDimensions != this->numberOfDimensions)
	{
		throw std::runtime_error("GetDistanceSquared error: points have different dimensions.");
	}
	else
	{
		double distanceSquared = 0;
		double difference;

		for (int i = 0; i < point.numberOfDimensions; i++)
		{
			difference = point.coordinates[i] - this->coordinates[i];
			distanceSquared += (difference * difference);
		}

		return distanceSquared;
	}
}

bool Point::IsTheSameAs(const Point& point) const
{
	bool arePointsTheSame = true;

	if (point.numberOfDimensions != this->numberOfDimensions)
	{
		arePointsTheSame = false;
	}
	else
	{
		for (int i = 0; i < point.numberOfDimensions; i++)
		{
			if (point.coordinates[i] != this->coordinates[i])
			{
				arePointsTheSame = false;
				break;
			}
		}
	}

	return arePointsTheSame;
}

void Point::Display() const
{
	std::cout << "( ";
	for (int i = 0; i < numberOfDimensions - 1; i++)
	{
		std::cout << coordinates[i] << ", ";
	}
	std::cout << coordinates[numberOfDimensions - 1] << " )";
}
