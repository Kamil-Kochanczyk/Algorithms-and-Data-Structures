#include <iostream>
#include <string>

template <typename T>
class ArrayStack
{
private:
	const int SIZE = 5;
	T* stack;
	int top;

public:
	ArrayStack()
	{
		this->stack = new T[SIZE];
		this->top = -1;
		std::cout << "ArrayStack created, SIZE = " << SIZE << std::endl;
	}

	~ArrayStack()
	{
		delete[] stack;
		std::cout << "ArrayStack destroyed" << std::endl;
	}

	bool IsEmpty()
	{
		return top == -1;
	}

	bool IsFull()
	{
		return top == SIZE - 1;
	}

	void Push(T value)
	{
		if (!IsFull())
		{
			top++;
			stack[top] = value;
		}
		else
		{
			throw std::exception("ArrayStack overflow");
		}
	}

	T Pop()
	{
		if (!IsEmpty())
		{
			return stack[top--];
		}
		else
		{
			throw std::exception("ArrayStack underflow");
		}
	}
};

template <typename T>
class Node
{
public:
	T value;
	Node* next;

	Node(T value)
	{
		this->value = value;
		this->next = nullptr;
	}
};

template <typename T>
class PointerStack
{
private:
	const int SIZE = 8;
	int counter;
	Node<T>* top;

public:
	PointerStack()
	{
		this->counter = 0;
		this->top = nullptr;
		std::cout << "PointerStack created, SIZE = " << SIZE << std::endl;
	}

	~PointerStack()
	{
		while (!IsEmpty())
		{
			Pop();
		}

		std::cout << "PointerStack destroyed" << std::endl;
	}

	bool IsEmpty()
	{
		return top == nullptr;
	}

	bool IsFull()
	{
		return counter == SIZE;
	}

	void Push(T value)
	{
		if (!IsFull())
		{
			Node<T>* newNode = new Node<T>(value);
			newNode->next = top;
			top = newNode;
			counter++;
		}
		else
		{
			throw std::exception("PointerStack overflow");
		}
	}

	T Pop()
	{
		if (!IsEmpty())
		{
			T valueAtTheTop = top->value;
			Node<T>* nodeAtTheTop = top;
			top = top->next;
			delete nodeAtTheTop;
			counter--;
			return valueAtTheTop;
		}
		else
		{
			throw std::exception("PointerStack underflow");
		}
	}
};

int main()
{
	ArrayStack<int> as;
	std::cout << std::endl;

	try
	{
		for (int i = 10; i < 100; i++)
		{
			as.Push(i);
			std::cout << "Pushed: " << i << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		int popped;

		for (int i = 10; i < 100; i++)
		{
			popped = as.Pop();
			std::cout << "Popped: " << popped << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	PointerStack<std::string> ps;
	std::cout << std::endl;

	try
	{
		for (int i = 10; i < 100; i++)
		{
			ps.Push(std::to_string(-1 * i));
			std::cout << "Pushed: " << -1 * i << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::string popped;

		for (int i = 10; i < 100; i++)
		{
			popped = ps.Pop();
			std::cout << "Popped: " << popped << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	return 0;
}
