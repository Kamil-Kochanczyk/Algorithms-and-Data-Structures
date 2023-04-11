#include "Algorithm.h"

void Algorithm::Swap(int* x, int* y)
{
	int auxiliary = *x;
	*x = *y;
	*y = auxiliary;
}

void Algorithm::BubbleSort(std::vector<int>& numbers)
{
	if (numbers.empty())
	{
		throw std::exception("Argument cannot be an empty vector");
	}

	bool swapped;
	int skip = 0;

	do
	{
		swapped = false;

		for (int i = 0; i < numbers.size() - skip - 1; i++)
		{
			if (numbers[i] > numbers[i + 1])
			{
				Algorithm::Swap(&numbers[i], &numbers[i + 1]);
				swapped = true;
			}
		}

		skip++;
	} while (swapped);
}

void Algorithm::SelectionSort(std::vector<int>& numbers)
{
	if (numbers.empty())
	{
		throw std::exception("Argument cannot be an empty vector");
	}

	int currentMinIndex;

	for (int i = 0; i < numbers.size() - 1; i++)
	{
		currentMinIndex = i;

		for (int j = i + 1; j < numbers.size(); j++)
		{
			if (numbers[j] < numbers[currentMinIndex])
			{
				currentMinIndex = j;
			}
		}

		if (currentMinIndex != i)
		{
			Algorithm::Swap(&numbers[i], &numbers[currentMinIndex]);
		}
	}
}

void Algorithm::InsertionSort(std::vector<int>& numbers)
{
	if (numbers.empty())
	{
		throw std::exception("Argument cannot be an empty vector");
	}

	for (int i = 0; i < numbers.size() - 1; i++)
	{
		int j = i + 1;

		while (j > 0 && numbers[j - 1] > numbers[j])
		{
			Algorithm::Swap(&numbers[j - 1], &numbers[j]);
			j--;
		}
	}
}

void Algorithm::MergeSort(std::vector<int>& numbers)
{
	if (numbers.size() >= 2)
	{
		int middle = numbers.size() / 2;
		std::vector<int> left;
		std::vector<int> right;

		for (int i = 0; i < numbers.size(); i++)
		{
			if (i < middle)
			{
				left.push_back(numbers[i]);
			}
			else
			{
				right.push_back(numbers[i]);
			}
		}

		MergeSort(left);
		MergeSort(right);
		Merge(left, right, numbers);
	}
}

void Algorithm::Merge(std::vector<int>& left, std::vector<int>& right, std::vector<int>& numbers)
{
	int i = 0, j = 0, k = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i] <= right[j])
		{
			numbers[k] = left[i];
			i++;
		}
		else
		{
			numbers[k] = right[j];
			j++;
		}

		k++;
	}

	while (i < left.size())
	{
		numbers[k] = left[i];
		i++;
		k++;
	}

	while (j < right.size())
	{
		numbers[k] = right[j];
		j++;
		k++;
	}
}

void Algorithm::QuickSort(std::vector<int>& numbers, int start, int end)
{
	if (start < end)
	{
		int pivotIndex = Partition(numbers, start, end);
		QuickSort(numbers, start, pivotIndex - 1);
		QuickSort(numbers, pivotIndex + 1, end);
	}
}

int Algorithm::Partition(std::vector<int>& numbers, int start, int end)
{
	int pivot = numbers[end];
	int finalPivotPosition = start;

	for (int i = start; i < end; i++)
	{
		if (numbers[i] <= pivot)
		{
			Algorithm::Swap(&numbers[i], &numbers[finalPivotPosition]);
			finalPivotPosition++;
		}
	}

	Algorithm::Swap(&numbers[finalPivotPosition], &numbers[end]);

	return finalPivotPosition;
}

void Algorithm::CountingSort(std::vector<int>& numbers)
{
	if (numbers.empty())
	{
		throw std::exception("Argument cannot be an empty vector");
	}

	int min = numbers[0];
	int max = numbers[0];

	for (auto number : numbers)
	{
		if (number < min)
		{
			min = number;
		}

		if (number > max)
		{
			max = number;
		}
	}

	int shift = (min < 0) ? abs(min) : 0;
	int length = max - min + 1;
	std::vector<int> occurrencesOfEachElement(length);

	for (auto number : numbers)
	{
		occurrencesOfEachElement[number + shift]++;
	}

	for (int i = 1; i < occurrencesOfEachElement.size(); i++)
	{
		occurrencesOfEachElement[i] += occurrencesOfEachElement[i - 1];
	}

	std::vector<int> startingPositions(occurrencesOfEachElement);

	for (int i = startingPositions.size() - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			startingPositions[i] = 0;
		}
		else
		{
			startingPositions[i] = startingPositions[i - 1];
		}
	}

	std::vector<int> sorted(numbers.size());

	for (auto number : numbers)
	{
		sorted[startingPositions[number + shift]] = number;
		startingPositions[number + shift]++;
	}

	numbers = sorted;
}

void Algorithm::HeapSort(std::vector<int>& numbers)
{
	for (int i = numbers.size() / 2 - 1; i >= 0; i--)
	{
		Heapify(numbers, numbers.size(), i);
	}

	for (int i = numbers.size() - 1; i > 0; i--)
	{
		Algorithm::Swap(&numbers[0], &numbers[i]);
		Heapify(numbers, i, 0);
	}
}

void Algorithm::Heapify(std::vector<int>& numbers, int size, int subtreeRoot)
{
	int largest = subtreeRoot;
	int leftChild = 2 * subtreeRoot + 1;
	int rightChild = 2 * subtreeRoot + 2;

	if (leftChild < size && numbers[leftChild] > numbers[largest])
	{
		largest = leftChild;
	}

	if (rightChild < size && numbers[rightChild] > numbers[largest])
	{
		largest = rightChild;
	}

	if (largest != subtreeRoot)
	{
		Algorithm::Swap(&numbers[subtreeRoot], &numbers[largest]);

		Heapify(numbers, size, largest);
	}
}