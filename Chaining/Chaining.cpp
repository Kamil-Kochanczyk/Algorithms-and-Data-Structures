#include <iostream>
#include <chrono>
#include <vector>

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
class LinkedList
{
private:
	Node<T>* head;

public:
	LinkedList() : head(nullptr)
	{

	}

	~LinkedList()
	{
		DeleteLinkedList();
	}

	void AddAtBeginning(T value)
	{
		Node<T>* newNode = new Node<T>(value);
		newNode->next = head;
		head = newNode;
	}

	Node<T>* Find(T value)
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

	void Remove(T value)
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

	void PrintLinkedList()
	{
		Node<T>* currentNode = head;

		while (currentNode != nullptr)
		{
			std::cout << currentNode->value << " -> ";
			currentNode = currentNode->next;
		}

		std::cout << "NULL" << std::endl;
	}

	void DeleteLinkedList()
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
};

class HashTable
{
private:
	const int SIZE;
	std::vector<LinkedList<int>> table;

public:
	HashTable(int size) : SIZE(size)
	{
		table.resize(SIZE);
	}

	~HashTable()
	{
		
	}

	int GetHash(int value)
	{
		return abs(value) % SIZE;
	}

	void Insert(int value)
	{
		int hash = GetHash(value);
		table[hash].AddAtBeginning(value);
	}

	Node<int>* Search(int value)
	{
		int hash = GetHash(value);
		return table[hash].Find(value);
	}

	void Delete(int value)
	{
		int hash = GetHash(value);
		table[hash].Remove(value);
	}

	void Display()
	{
		for (int i = 0; i < SIZE; i++)
		{
			std::cout << i << ":\t";
			table[i].PrintLinkedList();
		}
	}
};

int main()
{
	int size = 5;
	HashTable hashTable(size);

	hashTable.Display();
	std::cout << std::endl;

	hashTable.Insert(7);
	hashTable.Insert(11);
	hashTable.Insert(13);
	hashTable.Insert(-7);
	hashTable.Insert(5);
	hashTable.Insert(15);
	hashTable.Insert(-5);
	hashTable.Insert(5);

	hashTable.Display();
	std::cout << std::endl;

	Node<int>* found = hashTable.Search(13);

	if (found != nullptr)
	{
		std::cout << found->value << std::endl;
	}
	else
	{
		std::cout << "nullptr" << std::endl;
	}

	std::cout << std::endl;

	hashTable.Delete(13);
	hashTable.Delete(5);
	hashTable.Delete(13);

	hashTable.Display();
	std::cout << std::endl;

	found = hashTable.Search(13);

	if (found != nullptr)
	{
		std::cout << found->value << std::endl;
	}
	else
	{
		std::cout << "nullptr" << std::endl;
	}

	delete found;

	//int size = 10000;
	//HashTable hashTable(size);
	//std::vector<int> randomValues;

	//for (int i = 0; i < size; i++)
	//{
	//	randomValues.push_back((rand() % 101) - 50);
	//}

	//auto start = std::chrono::high_resolution_clock::now();
	//for (int value : randomValues)
	//{
	//	hashTable.Insert(value);
	//}
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli> milliseconds = end - start;
	//std::cout << "Insert: " << milliseconds.count() << std::endl;

	//start = std::chrono::high_resolution_clock::now();
	//for (int value : randomValues)
	//{
	//	hashTable.Search(value);
	//}
	//end = std::chrono::high_resolution_clock::now();
	//milliseconds = end - start;
	//std::cout << "Search: " << milliseconds.count() << std::endl;

	//start = std::chrono::high_resolution_clock::now();
	//for (int value : randomValues)
	//{
	//	hashTable.Delete(value);
	//}
	//end = std::chrono::high_resolution_clock::now();
	//milliseconds = end - start;
	//std::cout << "Delete: " << milliseconds.count() << std::endl;

	return 0;
}
