#include <iostream>
#include <fstream>
#include <chrono>


template <typename T>
class Node
{
public:
	T value;
	Node* next;

	Node(T v) : value(v), next(nullptr)
	{

	}
};


template <typename T>
void AddAtBeginning(Node<T>*& head, T value)
{
	Node<T>* newNode = new Node<T>(value);
	newNode->next = head;
	head = newNode;
}


template <typename T>
Node<T>* Find(Node<T>* head, T value)
{
	Node<T>* foundNode = nullptr;
	Node<T>* currentNode = head;

	while (currentNode != nullptr)
	{
		if (currentNode->value == value)
		{
			foundNode = currentNode;
			break;
		}

		currentNode = currentNode->next;
	}

	return foundNode;
}


template <typename T>
void Remove(Node<T>*& head, T value)
{
	Node<T>* currentNode = head;
	Node<T>* previousNode = nullptr;

	if (currentNode != nullptr && currentNode->value == value)
	{
		head = currentNode->next;
		delete currentNode;
	}
	else
	{
		while (currentNode != nullptr && currentNode->value != value)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}

		if (currentNode != nullptr && currentNode->value == value)
		{
			previousNode->next = currentNode->next;
			delete currentNode;
		}
	}
}


template <typename T>
void PrintLinkedList(Node<T>* head)
{
	Node<T>* currentNode = head;

	while (currentNode != nullptr)
	{
		std::cout << currentNode->value << " -> ";
		currentNode = currentNode->next;
	}

	std::cout << "NULL" << std::endl;
}


template <typename T>
void DeleteLinkedList(Node<T>*& head)
{
	Node<T>* currentNode = head;
	Node<T>* nextNode = nullptr;

	while (currentNode != nullptr)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}

	head = nullptr;
}


int main()
{
	Node<double>* head = nullptr;

	AddAtBeginning(head, 8.0);
	AddAtBeginning(head, 10.0);
	AddAtBeginning(head, 8.0);
	AddAtBeginning(head, 5.0);
	PrintLinkedList(head);
	std::cout << std::endl;

	double element = 5.0;
	Node<double>* found = Find(head, element);
	if (found != nullptr)
	{
		std::cout << element << " found" << std::endl;
		std::cout << found->value << std::endl;
	}
	else
	{
		std::cout << element << " not found" << std::endl;
	}
	std::cout << std::endl;

	Remove(head, 8.0);
	PrintLinkedList(head);
	std::cout << std::endl;

	DeleteLinkedList(head);
	PrintLinkedList(head);
	std::cout << std::endl;

	return 0;
}
