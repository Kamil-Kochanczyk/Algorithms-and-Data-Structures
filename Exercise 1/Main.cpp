#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "Algorithm.h"

template <typename T>
void ShowVector(std::vector<T>& v)
{
	for (auto element : v)
	{
		std::cout << element << "; ";
	}

	std::cout << std::endl;
}

int main()
{
	srand(time(nullptr));

	int n = 100;
	std::vector<int> numbers;

	for (int i = 0; i < n; i++)
	{
		numbers.push_back((rand() % n) - (n / 2));
	}

	std::cout << "1 - Bubble Sort\n2 - Selection Sort\n3 - Insertion Sort\n";
	std::cout << "4 - Merge Sort\n5 - Quick Sort\n";
	std::cout << "6 - Counting Sort\n7 - Heap Sort\n";
	
	unsigned short int algorithm;
	std::cout << "Choose an algorithm (1-7): ";
	std::cin >> algorithm;
	std::cout << "\n\n\n\n\n";

	std::string algorithmName;
	switch (algorithm)
	{
	case 1:
		algorithmName = "Bubble Sort";
		break;
	case 2:
		algorithmName = "Selection Sort";
		break;
	case 3:
		algorithmName = "Insertion Sort";
		break;
	case 4:
		algorithmName = "Merge Sort";
		break;
	case 5:
		algorithmName = "Quick Sort";
		break;
	case 6:
		algorithmName = "Counting Sort";
		break;
	case 7:
		algorithmName = "Heap Sort";
		break;
	default:
		algorithmName = "Invalid algorithm";
		break;
	}

	std::cout << "Original:\n";
	ShowVector<int>(numbers);
	std::cout << "\n\n\n\n\n";

	auto start = std::chrono::high_resolution_clock::now();
	switch (algorithm)
	{
	case 1:
		Algorithm::BubbleSort(numbers);
		break;
	case 2:
		Algorithm::SelectionSort(numbers);
		break;
	case 3:
		Algorithm::InsertionSort(numbers);
		break;
	case 4:
		Algorithm::MergeSort(numbers);
		break;
	case 5:
		Algorithm::QuickSort(numbers, 0, numbers.size() - 1);
		break;
	case 6:
		Algorithm::CountingSort(numbers);
		break;
	case 7:
		Algorithm::HeapSort(numbers);
		break;
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> milliseconds = end - start;
	double seconds = milliseconds.count() / 1000.0;

	std::cout << "Sorted:\n";
	ShowVector<int>(numbers);
	std::cout << "\n\n\n\n\n";

	if (algorithmName == "Invalid algorithm")
	{
		std::cout << "Your input was not correct\n";
		std::cout << "Vector could not be sorted\n";
	}
	else
	{
		std::cout << "You have chosen " << algorithmName << "\n";
		std::cout << "Vector has been sorted\n";
		std::cout << "Time: " << seconds << " s\n";
	}

	std::cout << "\n\n\n\n\n";

	/*
	std::ofstream output;

	if (algorithmName != "Invalid algorithm")
	{
		std::string path = ".\\" + algorithmName + ".txt";
		output.open(path, std::ios::trunc | std::ios::out);
	}

	if (output.is_open())
	{
		numbers.clear();

		int nMax = 5000;
		int step = 10;
		double timeInSeconds;

		for (int i = 0; i <= nMax; i += step)
		{
			std::vector<int> copy(numbers);

			if (i == 0)
			{
				timeInSeconds = 0;
			}
			else
			{
				auto startTime = std::chrono::high_resolution_clock::now();
				switch (algorithm)
				{
				case 1:
					Algorithm::BubbleSort(copy);
					break;
				case 2:
					Algorithm::SelectionSort(copy);
					break;
				case 3:
					Algorithm::InsertionSort(copy);
					break;
				case 4:
					Algorithm::MergeSort(copy);
					break;
				case 5:
					Algorithm::QuickSort(copy, 0, copy.size() - 1);
					break;
				case 6:
					Algorithm::CountingSort(copy);
					break;
				case 7:
					Algorithm::HeapSort(copy);
					break;
				}
				auto endTime = std::chrono::high_resolution_clock::now();

				std::chrono::duration<double, std::milli> timeInMilliseconds = endTime - startTime;
				timeInSeconds = timeInMilliseconds.count() / 1000.0;
			}

			output << i << "\t\t\t\t\t" << timeInSeconds << "\n";

			for (int j = 1; j <= step; j++)
			{
				numbers.push_back((rand() % n) - (n / 2));
			}
		}
	}
	else
	{
		std::cout << "Invalid algorithm";
	}
	*/
	
	return 0;
}