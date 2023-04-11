#include <iostream>

template <typename T>
class Node
{
public:
	T value;
	Node* next;

	Node(T value) : value(value), next(nullptr)
	{
		
	}
};

template <typename T>
class LinkedList
{
public:
	Node<T>* head;

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

	void DisplayLinkedList()
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

template <typename T>
class Set
{
private:
	LinkedList<T> linkedList;

public:
	Set() : linkedList()
	{

	}

	void Insert(T value)
	{
		if (!Contains(value))
		{
			linkedList.AddAtBeginning(value);
		}
	}

	bool Contains(T value)
	{
		return linkedList.Find(value) != nullptr;
	}

	void Remove(T value)
	{
		linkedList.Remove(value);
	}

	void Display()
	{
		linkedList.DisplayLinkedList();
	}

	static Set<T> Union(Set<T>& a, Set<T>& b)
	{
		Set<T> newSet;

		Node<T>* currentNode = a.linkedList.head;

		while (currentNode != nullptr)
		{
			newSet.Insert(currentNode->value);
			currentNode = currentNode->next;
		}

		currentNode = b.linkedList.head;

		while (currentNode != nullptr)
		{
			if (!newSet.Contains(currentNode->value))
			{
				newSet.Insert(currentNode->value);
			}

			currentNode = currentNode->next;
		}

		return newSet;
	}

	static Set<T> Intersection(Set<T>& a, Set<T>& b)
	{
		Set<T> newSet;

		Node<T>* currentNode = a.linkedList.head;

		while (currentNode != nullptr)
		{
			if (b.Contains(currentNode->value))
			{
				newSet.Insert(currentNode->value);
			}

			currentNode = currentNode->next;
		}

		return newSet;
	}

	static Set<T> Difference(Set<T>& a, Set<T>& b)
	{
		Set<T> newSet;

		Node<T>* currentNode = a.linkedList.head;

		while (currentNode != nullptr)
		{
			if (!b.Contains(currentNode->value))
			{
				newSet.Insert(currentNode->value);
			}

			currentNode = currentNode->next;
		}

		return newSet;
	}
};

int main()
{
	Set<std::string> a;

	a.Insert("a");
	a.Insert("b");
	a.Insert("c");
	a.Insert("a");
	a.Insert("b");
	a.Insert("a");
	a.Insert("c");
	a.Insert("d");
	a.Insert("e");
	a.Insert("f");

	a.Display();
	std::cout << std::endl;

	//std::string value = "d";
	//if (a.Contains(value))
	//{
	//	std::cout << "Value found\n\n";
	//}
	//else
	//{
	//	std::cout << "Value not found\n\n";
	//}

	//a.Remove(value);
	//a.Remove(value);

	//a.Display();
	//std::cout << std::endl;

	//if (a.Contains(value))
	//{
	//	std::cout << "Value found\n\n";
	//}
	//else
	//{
	//	std::cout << "Value not found\n\n";
	//}

	Set<std::string> b;

	b.Insert("e");
	b.Insert("f");
	b.Insert("g");
	b.Insert("h");
	b.Insert("i");
	b.Insert("j");
	b.Insert("e");
	b.Insert("f");
	b.Insert("e");
	b.Insert("f");

	b.Display();
	std::cout << std::endl;

	Set<std::string> u = Set<std::string>::Union(a, b);
	u.Display();
	std::cout << std::endl;

	Set<std::string> i = Set<std::string>::Intersection(a, b);
	i.Display();
	std::cout << std::endl;

	Set<std::string> d = Set<std::string>::Difference(a, b);
	d.Display();
	std::cout << std::endl;

	return 0;
}
