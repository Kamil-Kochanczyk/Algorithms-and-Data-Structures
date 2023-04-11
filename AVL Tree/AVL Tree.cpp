#include <iostream>

class Node
{
private:
	int value;
	Node* left;
	Node* right;
	int height;

public:
	Node(int value) : value(value), left(nullptr), right(nullptr), height(1)
	{

	}

	static int Height(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			return node->height;
		}
	}

	static int Balance(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			return Height(node->left) - Height(node->right);
		}
	}

	friend class AVLTree;
};

class AVLTree
{
public:
	Node* root;

public:
	AVLTree() : root(nullptr)
	{

	}

	Node* Insert(Node* node, int value)
	{
		if (node == nullptr)
		{
			return new Node(value);
		}

		if (value < node->value)
		{
			node->left = Insert(node->left, value);
		}
		else if (value > node->value)
		{
			node->right = Insert(node->right, value);
		}
		else
		{
			return node;
		}

		node->height = Max(Node::Height(node->left), Node::Height(node->right)) + 1;

		int balance = Node::Balance(node);

		if (balance > 1 && value < node->left->value)
		{
			return RightRotation(node);
		}

		if (balance > 1 && value > node->left->value)
		{
			node->left = LeftRotation(node->left);
			return RightRotation(node);
		}

		if (balance < -1 && value > node->right->value)
		{
			return LeftRotation(node);
		}

		if (balance < -1 && value < node->right->value)
		{
			node->right = RightRotation(node->right);
			return LeftRotation(node);
		}

		return node;
	}

	void Preorder(Node* root)
	{
		if (root != nullptr)
		{
			std::cout << root->value << std::endl;
			Preorder(root->left);
			Preorder(root->right);
		}
	}

private:
	int Max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	Node* RightRotation(Node* y)
	{
		if (y != nullptr && y->left != nullptr)
		{
			Node* x = y->left;
			y->left = x->right;
			x->right = y;

			y->height = Max(Node::Height(y->left), Node::Height(y->right)) + 1;
			x->height = Max(Node::Height(x->left), Node::Height(x->right)) + 1;

			return x;
		}
		else
		{
			throw std::runtime_error("RightRotation impossible to perform: required node is null");
		}
	}

	Node* LeftRotation(Node* x)
	{
		if (x != nullptr && x->right != nullptr)
		{
			Node* y = x->right;
			x->right = y->left;
			y->left = x;

			x->height = Max(Node::Height(x->left), Node::Height(x->right)) + 1;
			y->height = Max(Node::Height(y->left), Node::Height(y->right)) + 1;

			return y;
		}
		else
		{
			throw std::runtime_error("LeftRotation impossible to perform: required node is null");
		}
	}
};

int main()
{
	AVLTree tree;

	tree.root = tree.Insert(tree.root, 10);
	tree.root = tree.Insert(tree.root, 20);
	tree.root = tree.Insert(tree.root, 30);
	tree.root = tree.Insert(tree.root, 40);
	tree.root = tree.Insert(tree.root, 50);
	tree.root = tree.Insert(tree.root, 25);

	tree.Preorder(tree.root);

	return 0;
}
