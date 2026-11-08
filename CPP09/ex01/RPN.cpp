#include "RPN.hpp"
#include <sstream>
#include <cctype>
#include <climits>

RPN::RPN()
{
}

RPN::RPN(const RPN &other) : _stack(other._stack)
{
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
	}
	return *this;
}

RPN::~RPN()
{
}

static bool checkedMultiply(int left, int right, int &result)
{
	bool negative = (left < 0) != (right < 0);
	unsigned int a = left < 0 ? 0u - static_cast<unsigned int>(left)
		: static_cast<unsigned int>(left);
	unsigned int b = right < 0 ? 0u - static_cast<unsigned int>(right)
		: static_cast<unsigned int>(right);
	unsigned int negativeLimit = 0u - static_cast<unsigned int>(INT_MIN);
	unsigned int limit = negative ? negativeLimit : static_cast<unsigned int>(INT_MAX);
	if (a != 0 && b > limit / a)
		return false;
	unsigned int product = a * b;
	if (negative && product == negativeLimit)
		result = INT_MIN;
	else if (negative)
		result = -static_cast<int>(product);
	else
		result = static_cast<int>(product);
	return true;
}

bool RPN::applyOperator(char op)
{
	if (this->_stack.size() < 2)
	{
		return false;
	}

	int	right = this->_stack.top();
	this->_stack.pop();
	int	left = this->_stack.top();
	this->_stack.pop();

	if (op == '+')
	{
		if ((right > 0 && left > INT_MAX - right)
			|| (right < 0 && left < INT_MIN - right))
			return false;
		this->_stack.push(left + right);
	}
	else if (op == '-')
	{
		if ((right > 0 && left < INT_MIN + right)
			|| (right < 0 && left > INT_MAX + right))
			return false;
		this->_stack.push(left - right);
	}
	else if (op == '*')
	{
		int product = 0;
		if (!checkedMultiply(left, right, product))
			return false;
		this->_stack.push(product);
	}
	else if (op == '/')
	{
		if (right == 0 || (left == INT_MIN && right == -1))
		{
			return false;
		}
		this->_stack.push(left / right);
	}
	else
	{
		return false;
	}
	return true;
}

bool RPN::evaluate(const std::string &expression, int &result)
{
	while (!this->_stack.empty())
	{
		this->_stack.pop();
	}

	std::istringstream	tokens(expression);
	std::string			token;

	while (tokens >> token)
	{
		if (token.length() != 1)
		{
			return false;
		}

		char	c = token[0];

		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			this->_stack.push(c - '0');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (!this->applyOperator(c))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	if (this->_stack.size() != 1)
	{
		return false;
	}
	result = this->_stack.top();
	return true;
}
