#pragma once

#include <iostream>
#include <string>
#include <vector>

class Point
{
private:
	std::vector<double> coordinates;
	int numberOfDimensions;

public:
	Point(std::vector<double>& coordinates);

	const std::vector<double>& GetCoordinates() const;
	int GetNumberOfDimensions() const;

	double GetDistanceSquared(const Point& point) const;
	bool IsTheSameAs(const Point& point) const;
	void Display() const;
};
