#include <iostream>
#include <string>

template <typename T>
class Node
{
public:
	T value;
	Node* leftChild;
	Node* rightChild;

	Node(T value)
	{
		this->value = value;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
	}
};

template <typename T>
class BST
{
public:
	Node<T>* root;

	BST()
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
					// No duplicates allowed
					throw std::exception("Cannot insert the value to the BST. The value already exists in the BST.");
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

	Node<T>* Delete(T value)
	{
		if (root == nullptr)
		{
			throw std::exception("Cannot delete the value from the BST. The BST is empty.");
		}
		else
		{
			Node<T>* deleted = nullptr;
			Node<T>* current = root;
			Node<T>* parent = nullptr;

			while (current != nullptr && current->value != value)
			{
				parent = current;

				if (value < current->value)
				{
					current = current->leftChild;
				}
				else
				{
					current = current->rightChild;
				}
			}

			// If current is not nullptr, then it represents the node that will be deleted
			if (current != nullptr && current->value == value)
			{
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
					}
					else
					{
						root = nullptr;
					}

					delete current;
				}
				// Case 2: node that will be deleted has one child
				else if (current->leftChild == nullptr || current->rightChild == nullptr)
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
					delete current;
				}
				// Case 3: node that will be deleted has two children
				else
				{
					Node<T>* min = current->rightChild;
					Node<T>* minParent = current;

					while (min->leftChild != nullptr)
					{
						minParent = min;
						min = min->leftChild;
					}

					current->value = min->value;

					if (minParent->value != current->value)
					{
						minParent->leftChild = nullptr;
					}

					if (min->rightChild != nullptr)
					{
						minParent->leftChild = min->rightChild;
					}

					if (minParent->value == current->value && min->leftChild == nullptr)
					{
						current->rightChild = min->rightChild;
					}

					delete min;
				}

				deleted = new Node<T>(value);
			}

			return deleted;
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

int main()
{
	try
	{
		BST<int> bst;
		bst.PreorderDisplay(bst.root);

		bst.Insert(25);
		bst.Insert(20);
		bst.Insert(36);
		bst.Insert(10);
		bst.Insert(22);
		bst.Insert(30);
		bst.Insert(40);
		bst.Insert(5);
		bst.Insert(12);
		bst.Insert(28);
		bst.Insert(38);
		bst.Insert(48);
		bst.PreorderDisplay(bst.root);
		std::cout << std::endl << std::endl;

		bst.Delete(25);
		bst.PreorderDisplay(bst.root);
		std::cout << std::endl << std::endl;

		Node<int>* find;
		int number = 10;
		find = bst.Search(number);

		if (find == nullptr)
		{
			std::cout << number << " not found" << std::endl;
		}
		else
		{
			std::cout << "Value: " << find->value << std::endl;

			if (find->leftChild != nullptr)
			{
				std::cout << "Left child: " << find->leftChild->value << std::endl;
			}

			if (find->rightChild != nullptr)
			{
				std::cout << "Right child: " << find->rightChild->value << std::endl;
			}
		}

		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
