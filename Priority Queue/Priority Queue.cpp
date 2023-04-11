#include <iostream>
#include <cmath>
#include <vector>

/*
 * Indexing:
 *
 * 1. If parentIndex = i, then leftChildIndex = 2 * i + 1, rightChildIndex = 2 * i + 2
 *
 * 2. If leftChildIndex = i, then rightChildIndex = i + 1, parentIndex = (i - 1) / 2
 *
 * 3. If rightChildIndex = i, then leftChildIndex = i - 1, parentIndex = (i - 2) / 2
 */

template <typename T>
class Node
{
private:
	T value;
	int priority;

public:
	Node(T value, int priority) : value(value), priority(priority)
	{
		
	}

	T getValue()
	{
		return value;
	}

	int getPriority()
	{
		return priority;
	}
};

template <typename T>
class PriorityQueue
{
private:
	std::vector<Node<T>> maxHeap;

public:
	void put(T value, int priority)
	{
		Node<T> newNode(value, priority);
		maxHeap.push_back(newNode);

		if (maxHeap.size() > 1)
		{
			int newNodeIndex = maxHeap.size() - 1;
			compareChildWithParent(newNodeIndex);
		}
	}

	Node<T> get()
	{
		if (isEmpty())
		{
			throw std::runtime_error("Priority queue is empty");
		}

		Node<T> node = front();
		maxHeap[0] = maxHeap[maxHeap.size() - 1];
		maxHeap.pop_back();
		heapify(0);

		return node;
	}

	Node<T> front()
	{
		if (isEmpty())
		{
			throw std::runtime_error("Priority queue is empty");
		}

		return maxHeap[0];
	}

	bool isEmpty()
	{
		return maxHeap.empty();
	}

	void makeNull()
	{
		maxHeap.clear();
	}

private:
	void compareChildWithParent(int childIndex)
	{
		if (childIndex > 0)
		{
			bool isLeftChild = false;
			bool isRightChild = false;
			double parentIndexIfLeftChild = (childIndex - 1) / 2.0;
			double parentIndexIfRightChild = (childIndex - 2) / 2.0;
			double parentIndex;

			if (parentIndexIfLeftChild == floor(parentIndexIfLeftChild))
			{
				isLeftChild = true;
			}
			else if (parentIndexIfRightChild == floor(parentIndexIfRightChild))
			{
				isRightChild = true;
			}

			if (isLeftChild)
			{
				parentIndex = parentIndexIfLeftChild;
			}
			else if (isRightChild)
			{
				parentIndex = parentIndexIfRightChild;
			}

			if (maxHeap[childIndex].getPriority() > maxHeap[parentIndex].getPriority())
			{
				std::swap(maxHeap[childIndex], maxHeap[parentIndex]);
				compareChildWithParent(parentIndex);
			}
		}
	}

	void heapify(int index)
	{
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int largest = index;

		if (leftChild < maxHeap.size() && maxHeap[leftChild].getPriority() > maxHeap[largest].getPriority())
		{
			largest = leftChild;
		}

		if (rightChild < maxHeap.size() && maxHeap[rightChild].getPriority() > maxHeap[largest].getPriority())
		{
			largest = rightChild;
		}

		if (largest != index)
		{
			std::swap(maxHeap[index], maxHeap[largest]);
			heapify(largest);
		}
	}
};

int main()
{
	PriorityQueue<std::string> pq;

	pq.put("a", 13);
	pq.put("b", 7);
	pq.put("c", 23);
	pq.put("d", -1);
	pq.put("e", 0);
	pq.put("f", -13);
	pq.put("g", 1);
	pq.put("h", 3);
	pq.put("i", 2);
	pq.put("k", 3);
	pq.put("l", 999);
	pq.put("m", -999);
	pq.put("n", 3);
	pq.put("o", 0);
	pq.put("p", -1);

	while (!pq.isEmpty())
	{
		std::cout << pq.front().getValue() << ", " << pq.front().getPriority() << "\n";

		Node<std::string> node = pq.get();
		std::cout << node.getValue() << ", " << node.getPriority() << "\n\n";
	}

	pq.makeNull();

	try
	{
		//pq.front();
		pq.get();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
