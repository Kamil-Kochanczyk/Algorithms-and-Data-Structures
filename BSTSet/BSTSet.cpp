#include <iostream>

template <typename T>
class Node
{
public:
	T value;
	Node* leftChild;
	Node* rightChild;
	Node* parent;

	Node(T value)
	{
		this->value = value;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
		this->parent = nullptr;
	}
};

template <typename T>
class BinarySearchTree
{
public:
	Node<T>* root;

	BinarySearchTree()
	{
		this->root = nullptr;
	}

	void Insert(T value)
	{
		Node<T>* newNode = new Node<T>(value);

		if (root == nullptr)
		{
			root = newNode;
		}
		else
		{
			Node<T>* current = root;
			Node<T>* parent = nullptr;
			bool currentWentLeft;

			while (current != nullptr)
			{
				if (value < current->value)
				{
					parent = current;
					current = current->leftChild;
					currentWentLeft = true;
				}
				else if (value > current->value)
				{
					parent = current;
					current = current->rightChild;
					currentWentLeft = false;
				}
				else
				{
					// Duplicate
					return;
				}
			}

			if (currentWentLeft)
			{
				parent->leftChild = newNode;
			}
			else
			{
				parent->rightChild = newNode;
			}

			newNode->parent = parent;
		}
	}

	Node<T>* Search(T value)
	{
		Node<T>* found = nullptr;
		Node<T>* current = root;

		while (current != nullptr)
		{
			if (value < current->value)
			{
				current = current->leftChild;
			}
			else if (value > current->value)
			{
				current = current->rightChild;
			}
			else
			{
				found = current;
				break;
			}
		}

		return found;
	}

	void Delete(T value)
	{
		if (root == nullptr)
		{
			// Binary Search Tree is empty
			return;
		}

		Node<T>* current = Search(value);

		// If current is not nullptr, then it represents the node that will be deleted
		if (current != nullptr)
		{
			Node<T>* parent = current->parent;

			// Case 1: node that will be deleted has no children
			if (current->leftChild == nullptr && current->rightChild == nullptr)
			{
				if (parent != nullptr)
				{
					if (parent->leftChild != nullptr && parent->leftChild->value == value)
					{
						parent->leftChild = nullptr;
					}

					if (parent->rightChild != nullptr && parent->rightChild->value == value)
					{
						parent->rightChild = nullptr;
					}

					delete current;
				}
				else
				{
					delete current;
					root = nullptr;
				}
			}
			// Case 2: node that will be deleted has two children
			else if (current->leftChild != nullptr && current->rightChild != nullptr)
			{
				Node<T>* min = current->rightChild;

				while (min->leftChild != nullptr)
				{
					min = min->leftChild;
				}

				T minValue = min->value;
				Delete(minValue);
				current->value = minValue;
			}
			// Case 3: node that will be deleted has one child
			else
			{
				parent = current;

				if (current->leftChild != nullptr)
				{
					current->value = current->leftChild->value;
					current = current->leftChild;
				}
				else
				{
					current->value = current->rightChild->value;
					current = current->rightChild;
				}

				parent->leftChild = current->leftChild;
				parent->rightChild = current->rightChild;

				if (parent->leftChild != nullptr)
				{
					parent->leftChild->parent = parent;
				}

				if (parent->rightChild != nullptr)
				{
					parent->rightChild->parent = parent;
				}

				delete current;
			}
		}
	}

	void PreorderDisplay(Node<T>* node)
	{
		if (node != nullptr)
		{
			std::cout << node->value << "; ";

			if (node->leftChild != nullptr)
			{
				PreorderDisplay(node->leftChild);
			}

			if (node->rightChild != nullptr)
			{
				PreorderDisplay(node->rightChild);
			}
		}
	}
};

template <typename T>
class Set
{
public:
	BinarySearchTree<T> binarySearchTree;

	Set() : binarySearchTree()
	{
		
	}

	void Insert(T value)
	{
		binarySearchTree.Insert(value);
	}

	bool Contains(T value)
	{
		return binarySearchTree.Search(value) != nullptr;
	}

	void Remove(T value)
	{
		binarySearchTree.Delete(value);
	}

	void Display()
	{
		binarySearchTree.PreorderDisplay(binarySearchTree.root);
	}

	static Set<T> Union(Set<T>& a, Set<T>& b)
	{
		Set<T> u;
		AddAll(a.binarySearchTree.root, u);
		AddAll(b.binarySearchTree.root, u);
		return u;
	}

	static Set<T> Intersection(Set<T>& a, Set<T>& b)
	{
		Set<T> i;
		GetIntersection(a.binarySearchTree.root, b, i);
		return i;
	}

	static Set<T> Difference(Set<T>& a, Set<T>& b)
	{
		Set<T> d;
		GetDifference(a.binarySearchTree.root, b, d);
		return d;
	}

private:
	static void AddAll(Node<T>* sourceRoot, Set<T>& destination)
	{
		if (sourceRoot != nullptr)
		{
			destination.Insert(sourceRoot->value);

			if (sourceRoot->leftChild != nullptr)
			{
				AddAll(sourceRoot->leftChild, destination);
			}

			if (sourceRoot->rightChild != nullptr)
			{
				AddAll(sourceRoot->rightChild, destination);
			}
		}
	}

	static void GetIntersection(Node<T>* aRoot, Set<T>& b, Set<T>& i)
	{
		if (aRoot != nullptr)
		{
			if (b.Contains(aRoot->value))
			{
				i.Insert(aRoot->value);
			}

			if (aRoot->leftChild != nullptr)
			{
				GetIntersection(aRoot->leftChild, b, i);
			}

			if (aRoot->rightChild != nullptr)
			{
				GetIntersection(aRoot->rightChild, b, i);
			}
		}
	}

	static void GetDifference(Node<T>* aRoot, Set<T>& b, Set<T>& d)
	{
		if (aRoot != nullptr)
		{
			if (!b.Contains(aRoot->value))
			{
				d.Insert(aRoot->value);
			}

			if (aRoot->leftChild != nullptr)
			{
				GetDifference(aRoot->leftChild, b, d);
			}

			if (aRoot->rightChild != nullptr)
			{
				GetDifference(aRoot->rightChild, b, d);
			}
		}
	}
};

int main()
{
	Set<char> a;

	a.Insert('q');
	a.Insert('w');
	a.Insert('e');
	a.Insert('r');
	a.Insert('t');
	a.Insert('y');

	a.Display();
	std::cout << "\n\n";

	Set<char> b;

	b.Insert('b');
	b.Insert('s');
	b.Insert('t');
	b.Insert('s');
	b.Insert('e');
	b.Insert('t');

	b.Display();
	std::cout << "\n\n";

	Set<char> u = Set<char>::Union(a, b);
	u.Display();
	std::cout << "\n\n";

	Set<char> i = Set<char>::Intersection(a, b);
	i.Display();
	std::cout << "\n\n";

	Set<char> d = Set<char>::Difference(a, b);
	d.Display();
	std::cout << "\n\n";

	return 0;
}
