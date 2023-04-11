#include <iostream>
#include <vector>

template <typename T>
class Stack
{
private:
	const int SIZE = 100;
	T* stack;
	int top;

public:
	Stack()
	{
		this->stack = new T[SIZE];
		this->top = -1;
	}

	~Stack()
	{
		delete[] stack;
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
			throw std::exception("Stack overflow");
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
			throw std::exception("Stack underflow");
		}
	}
};

class ReversePolishNotation
{
public:
	static std::vector<std::string> Split(std::string expression, std::string delimiter)
	{
		std::vector<std::string> tokens;

		auto start = 0U;
		auto end = expression.find(delimiter);

		while (end != std::string::npos)
		{
			tokens.push_back(expression.substr(start, end - start));
			start = end + delimiter.length();
			end = expression.find(delimiter, start);
		}

		tokens.push_back(expression.substr(start, end));

		return tokens;
	}

	static double Evaluate(std::string rpnExpression)
	{
		std::vector<std::string> tokens = Split(rpnExpression, " ");
		Stack<double> stack;

		for (std::string token : tokens)
		{
			if (token == "+")
			{
				double rightOperand = stack.Pop();
				double leftOperand = stack.Pop();
				stack.Push(leftOperand + rightOperand);
			}
			else if (token == "-")
			{
				double rightOperand = stack.Pop();
				double leftOperand = stack.Pop();
				stack.Push(leftOperand - rightOperand);
			}
			else if (token == "*")
			{
				double rightOperand = stack.Pop();
				double leftOperand = stack.Pop();
				stack.Push(leftOperand * rightOperand);
			}
			else if (token == "/")
			{
				double rightOperand = stack.Pop();
				double leftOperand = stack.Pop();
				stack.Push(leftOperand / rightOperand);
			}
			else if (token == "^")
			{
				double exponent = stack.Pop();
				double base = stack.Pop();
				stack.Push(pow(base, exponent));
			}
			else if (token == "sqrt")
			{
				double number = stack.Pop();
				stack.Push(sqrt(number));
			}
			else
			{
				// If token isn't any of the above operators, we assume that it's just a number and we push this number to the stack
				stack.Push(atof(token.c_str()));
			}
		}

		return stack.Pop();
	}
};

int main()
{
	std::string rpnExpression = "16 4 * sqrt 2 -3 ^ 8 * 0.25 + / 0.25 sqrt -";
	double result = ReversePolishNotation::Evaluate(rpnExpression);
	std::cout << result << std::endl;

	return 0;
}
