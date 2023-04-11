#include <iostream>
#include <vector>
#include "Point.h"
#include "Node.h"
#include "KdTree.h"
#include "PointsBase.h"

void ResetCIN()
{
	std::cin.clear();
	std::cin.ignore(INT32_MAX, '\n');
}

int main()
{
	int numberOfDimensions;
	std::cout << "Enter the number of space dimensions." << std::endl;
	if (!(std::cin >> numberOfDimensions) || numberOfDimensions <= 0)
	{
		std::cout << "Invalid input. Number of space dimensions should be a positive integer." << std::endl;
		return -1;
	}
	std::cout << std::endl;
	ResetCIN();

	PointsBase base(numberOfDimensions);

	std::cout << "Choose an operation 1, 2, 3 or 4. Enter anything else to exit the program." << std::endl;
	std::cout << "1. Insert a new point to the base." << std::endl;
	std::cout << "2. Search for a point in the base." << std::endl;
	std::cout << "3. Find the closest point in the base relative to the specified point." << std::endl;
	std::cout << "4. Display all points in the base." << std::endl;
	std::cout << std::endl;

	int option;
	bool endProgram = false;

	do
	{
		std::cout << "Option: ";
		std::cin >> option;
		ResetCIN();

		if (option == 1 || option == 2 || option == 3)
		{
			std::vector<double> coordinates;
			double coordinate;

			std::cout << "Specify the coordinates of the point." << std::endl;

			for (int i = 0; i < numberOfDimensions; i++)
			{
				std::cout << "Coordinate " << i + 1 << ": ";
				std::cin >> coordinate;
				ResetCIN();
				coordinates.push_back(coordinate);
			}

			Point point(coordinates);

			std::cout << "Your point: ";
			point.Display();
			std::cout << std::endl;

			if (option == 1)
			{
				base.Insert(point);
				std::cout << "Your point has been added to the base." << std::endl;
			}
			else if (option == 2)
			{
				Node* found = base.Search(point);
				std::cout << "Your point " << ((found != nullptr) ? "has" : "has not") << " been found in the base." << std::endl;
			}
			else
			{
				Node* closest = base.FindClosestPoint(point);

				if (closest != nullptr)
				{
					std::cout << "This is the closest point in the base to your point: ";
					closest->GetPoint().Display();
				}
				else
				{
					std::cout << "No point has been found in the base (the base is currently empty).";
				}

				std::cout << std::endl;
			}
		}
		else if (option == 4)
		{
			base.Display();
		}
		else
		{
			endProgram = true;
		}
		
		std::cout << std::endl;
	} while (!endProgram);

	return 0;
}
