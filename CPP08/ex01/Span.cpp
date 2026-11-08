#include "Span.hpp"
#include <algorithm>
#include <limits>

Span::Span() : _maxSize(0)
{
}

Span::Span(unsigned int n) : _maxSize(n)
{
	this->_numbers.reserve(n);
}

Span::Span(const Span &other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_maxSize = other._maxSize;
		this->_numbers = other._numbers;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (this->_numbers.size() >= this->_maxSize)
	{
		throw Span::SpanFullException();
	}
	this->_numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
	if (this->_numbers.size() < 2)
	{
		throw Span::NoSpanException();
	}

	std::vector<int>	sorted(this->_numbers);
	std::sort(sorted.begin(), sorted.end());

	unsigned int	shortest = std::numeric_limits<unsigned int>::max();
	for (size_t i = 1; i < sorted.size(); i++)
	{
		unsigned int	diff = static_cast<unsigned int>(sorted[i])
			- static_cast<unsigned int>(sorted[i - 1]);
		if (diff < shortest)
		{
			shortest = diff;
		}
	}
	return shortest;
}

unsigned int Span::longestSpan() const
{
	if (this->_numbers.size() < 2)
	{
		throw Span::NoSpanException();
	}

	int	minValue = *std::min_element(this->_numbers.begin(), this->_numbers.end());
	int	maxValue = *std::max_element(this->_numbers.begin(), this->_numbers.end());
	return static_cast<unsigned int>(maxValue) - static_cast<unsigned int>(minValue);
}

Span::SpanFullException::SpanFullException()
{
}

Span::SpanFullException::SpanFullException(const SpanFullException &other) : std::exception(other)
{
}

Span::SpanFullException &Span::SpanFullException::operator=(const SpanFullException &other)
{
	if (this != &other)
	{
		std::exception::operator=(other);
	}
	return *this;
}

Span::SpanFullException::~SpanFullException() throw()
{
}

const char *Span::SpanFullException::what() const throw()
{
	return "Span is already full!";
}

Span::NoSpanException::NoSpanException()
{
}

Span::NoSpanException::NoSpanException(const NoSpanException &other) : std::exception(other)
{
}

Span::NoSpanException &Span::NoSpanException::operator=(const NoSpanException &other)
{
	if (this != &other)
	{
		std::exception::operator=(other);
	}
	return *this;
}

Span::NoSpanException::~NoSpanException() throw()
{
}

const char *Span::NoSpanException::what() const throw()
{
	return "No span can be found!";
}
