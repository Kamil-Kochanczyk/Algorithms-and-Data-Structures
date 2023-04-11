#include <iostream>
#include <fstream>
#include <chrono>


template <typename T>
class Node
{
public:
	int previous;
	T value;
	int next;
};


template <typename T>
void AddAtBeginning(T value, Node<T> nodes[], bool availableIndexes[], int size)
{
	int index = -1;

	for (int i = 0; i < size; i++)
	{
		if (availableIndexes[i] == true)
		{
			index = i;
			availableIndexes[i] = false;
			break;
		}
	}

	if (index != -1)
	{
		nodes[index].value = value;
		nodes[index].next = nodes[0].next;
		nodes[index].previous = -1;
		nodes[nodes[0].next].previous = index;
		nodes[0].next = index;
	}
}


template <typename T>
int Find(T value, Node<T> nodes[])
{
	int foundIndex = -1;
	int currentIndex = 0;
	Node<T> currentNode = nodes[currentIndex];

	while (currentNode.next != -1 && currentNode.value != value)
	{
		currentIndex = currentNode.next;
		currentNode = nodes[currentIndex];
	}

	if (currentNode.next != nodes[0].next && currentNode.value == value)
	{
		foundIndex = currentIndex;
	}

	return foundIndex;
}


template <typename T>
void Remove(T value, Node<T> nodes[], bool availableIndexes[])
{
	Node<T> currentNode = nodes[0];
	int currentIndex = 0;

	if (currentNode.next != -1 && nodes[currentNode.next].value == value)
	{
		availableIndexes[currentNode.next] = true;
		nodes[currentIndex].next = nodes[currentNode.next].next;
		nodes[nodes[currentNode.next].next].previous = -1;
	}
	else
	{
		if (currentNode.next != -1)
		{
			currentIndex = currentNode.next;
			currentNode = nodes[currentIndex];
		}

		while (currentNode.next != -1 && currentNode.value != value)
		{
			currentIndex = currentNode.next;
			currentNode = nodes[currentIndex];
		}

		if (currentNode.next != -1 && currentNode.value == value)
		{
			availableIndexes[currentIndex] = true;
			nodes[currentNode.previous].next = currentNode.next;
			nodes[currentNode.next].previous = currentNode.previous;
		}

		if (currentNode.next == -1 && currentNode.value == value)
		{
			availableIndexes[currentIndex] = true;
			nodes[currentNode.previous].next = -1;
		}
	}
}


template <typename T>
void PrintLinkedList(Node<T> nodes[])
{
	Node<T> currentNode = nodes[0];

	std::cout << "Head -> ... -> Last:\t";
	while (currentNode.next != -1)
	{
		currentNode = nodes[currentNode.next];
		std::cout << currentNode.value << " -> ";
	}
	std::cout << "NULL" << std::endl;

	std::cout << "Last -> ... -> Head:\t";
	while (currentNode.previous != -1)
	{
		std::cout << currentNode.value << " -> ";
		currentNode = nodes[currentNode.previous];
	}
	if (nodes[0].next != -1 && nodes[nodes[0].next].next == currentNode.next)
	{
		std::cout << currentNode.value << " -> ";
	}
	std::cout << "NULL" << std::endl;
}


template <typename T>
void DeleteLinkedList(Node<T> nodes[], bool availableIndexes[], int size)
{
	nodes[0].next = -1;
	std::fill(availableIndexes + 1, availableIndexes + size, true);
}


int main()
{
	const int SIZE = 5;

	Node<std::string> nodes[SIZE];
	nodes[0].next = -1;
	nodes[0].previous = -1;

	bool availableIndexes[SIZE];
	availableIndexes[0] = false;
	std::fill(availableIndexes + 1, availableIndexes + SIZE, true);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	AddAtBeginning((std::string)"One", nodes, availableIndexes, SIZE);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	AddAtBeginning((std::string)"Two", nodes, availableIndexes, SIZE);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	AddAtBeginning((std::string)"Three", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Three", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Four", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Five", nodes, availableIndexes, SIZE);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	std::string element = "Two";
	int found = Find(element, nodes);
	if (found != -1)
	{
		std::cout << element << " found" << std::endl;
		std::cout << nodes[found].value << std::endl;
	}
	else
	{
		std::cout << element << " not found" << std::endl;
	}
	std::cout << std::endl;

	DeleteLinkedList(nodes, availableIndexes, SIZE);
	PrintLinkedList(nodes);
	std::cout << std::endl;

	AddAtBeginning((std::string)"Six", nodes, availableIndexes, SIZE);
	PrintLinkedList(nodes);
	std::cout << std::endl;

	found = Find(element, nodes);
	if (found != -1)
	{
		std::cout << element << " found" << std::endl;
		std::cout << nodes[found].value << std::endl;
	}
	else
	{
		std::cout << element << " not found" << std::endl;
	}
	std::cout << std::endl;

	AddAtBeginning((std::string)"Seven", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Eight", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Nine", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Ten", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Eleven", nodes, availableIndexes, SIZE);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	Remove((std::string)"Six", nodes, availableIndexes);
	Remove((std::string)"Nine", nodes, availableIndexes);
	Remove((std::string)"Nine", nodes, availableIndexes);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	AddAtBeginning((std::string)"Ten", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Eleven", nodes, availableIndexes, SIZE);
	AddAtBeginning((std::string)"Twelve", nodes, availableIndexes, SIZE);

	PrintLinkedList(nodes);
	std::cout << std::endl;

	DeleteLinkedList(nodes, availableIndexes, SIZE);
	PrintLinkedList(nodes);
	std::cout << std::endl;

	return 0;
}
