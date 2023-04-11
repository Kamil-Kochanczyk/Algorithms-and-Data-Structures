#include <iostream>
#include <fstream>
#include <chrono>


template <typename T>
class Node
{
public:
	Node* previous;
	T value;
	Node* next;

	Node(T v) : previous(nullptr), value(v), next(nullptr)
	{

	}
};


template <typename T>
void AddAtBeginning(Node<T>*& head, T value)
{
	Node<T>* newNode = new Node<T>(value);

	if (head != nullptr)
	{
		newNode->next = head;
		head->previous = newNode;
	}

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

	if (currentNode != nullptr && currentNode->value == value)
	{
		if (currentNode->next != nullptr)
		{
			currentNode->next->previous = currentNode->previous;
		}

		head = currentNode->next;
		delete currentNode;
	}
	else
	{
		while (currentNode != nullptr && currentNode->value != value)
		{
			currentNode = currentNode->next;
		}

		if (currentNode != nullptr && currentNode->value == value)
		{
			if (currentNode->next != nullptr)
			{
				currentNode->next->previous = currentNode->previous;
			}

			if (currentNode->previous != nullptr)
			{
				currentNode->previous->next = currentNode->next;
			}

			delete currentNode;
		}
	}
}


template <typename T>
void PrintLinkedList(Node<T>* head)
{
	Node<T>* currentNode = head;
	Node<T>* lastNode = nullptr;

	std::cout << "Head -> ... -> Last:\t";
	while (currentNode != nullptr)
	{
		std::cout << currentNode->value << " -> ";
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	std::cout << "NULL" << std::endl;

	currentNode = lastNode;

	std::cout << "Last -> ... -> Head:\t";
	while (currentNode != nullptr)
	{
		std::cout << currentNode->value << " -> ";
		currentNode = currentNode->previous;
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
	Node<int>* head = nullptr;

	AddAtBeginning(head, 1);
	AddAtBeginning(head, 3);
	AddAtBeginning(head, 1);
	AddAtBeginning(head, 0);
	PrintLinkedList(head);
	std::cout << std::endl;

	int element = 3;
	Node<int>* found = Find(head, element);
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

	Remove(head, 1);
	PrintLinkedList(head);
	std::cout << std::endl;

	DeleteLinkedList(head);
	PrintLinkedList(head);
	std::cout << std::endl;

	return 0;
}
