#include <iostream>

class Node
{
public:
	int value;
	Node* left;
	Node* right;

public:
	Node(int value) : value(value), left(nullptr), right(nullptr)
	{

	}

	friend class SplayTree;
};

class SplayTree
{
public:
	Node* root;

public:
	SplayTree() : root(nullptr)
	{

	}

	Node* Search(Node* root, int value)
	{
		return Splay(root, value);
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
	Node* RightRotation(Node* y)
	{
		if (y != nullptr && y->left != nullptr)
		{
			Node* x = y->left;
			y->left = x->right;
			x->right = y;
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
			return y;
		}
		else
		{
			throw std::runtime_error("LeftRotation impossible to perform: required node is null");
		}
	}

	Node* Splay(Node* root, int value)
	{
		if (root == nullptr || root->value == value)
		{
			return root;
		}

		if (value < root->value)
		{
			if (root->left == nullptr)
			{
				return root;
			}

			if (value < root->left->value)
			{
				root->left->left = Splay(root->left->left, value);
				root = RightRotation(root);
			}
			else if (value > root->left->value)
			{
				root->left->right = Splay(root->left->right, value);
				
				if (root->left->right != nullptr)
				{
					root->left = LeftRotation(root->left);
				}
			}

			return (root->left == nullptr) ? root : RightRotation(root);
		}
		else
		{
			if (root->right == nullptr)
			{
				return root;
			}

			if (value > root->right->value)
			{
				root->right->right = Splay(root->right->right, value);
				root = LeftRotation(root);
			}
			else if (value < root->right->value)
			{
				root->right->left = Splay(root->right->left, value);

				if (root->right->left != nullptr)
				{
					root->right = RightRotation(root->right);
				}
			}

			return (root->right == nullptr) ? root : LeftRotation(root);
		}
	}
};

int main()
{
	SplayTree tree;

	tree.root = new Node(100);
	tree.root->left = new Node(50);
	tree.root->right = new Node(200);
	tree.root->left->left = new Node(40);
	tree.root->left->left->left = new Node(30);
	tree.root->left->left->left->left = new Node(20);

	tree.root = tree.Search(tree.root, 20);

	tree.Preorder(tree.root);

	return 0;
}
