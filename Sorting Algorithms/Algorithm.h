#pragma once
#include <vector>

class Algorithm
{
public:
	static void Swap(int* x, int* y);

	static void BubbleSort(std::vector<int>& numbers);

	static void SelectionSort(std::vector<int>& numbers);

	static void InsertionSort(std::vector<int>& numbers);

	static void MergeSort(std::vector<int>& numbers);

	static void QuickSort(std::vector<int>& numbers, int start, int end);

	static void CountingSort(std::vector<int>& numbers);

	static void HeapSort(std::vector<int>& numbers);

private:
	static void Merge(std::vector<int>& left, std::vector<int>& right, std::vector<int>& numbers);

	static int Partition(std::vector<int>& numbers, int start, int end);

	static void Heapify(std::vector<int>& numbers, int size, int subtreeRoot);
};